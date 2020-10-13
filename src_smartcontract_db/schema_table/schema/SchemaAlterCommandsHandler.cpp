/*
 * SchemaAlterCommandsHandler.cpp
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#include "schema_table/schema/SchemaAlterCommandsHandler.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "trx/transaction_log_alter/AlterAddIndexCommandLog.h"
#include "trx/transaction_log_alter/AlterAddColumnCommandLog.h"
#include "trx/transaction_log_alter/AlterDropIndexCommandLog.h"
#include "trx/transaction_log_alter/AlterDropColumnCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterModifyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterRenameColumnCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/schema/SchemaManager.h"
#include "schema_table/schema/SchemaRoot.h"

#include "schema_table/schema_alter_ctx/ColumnModifyContext.h"
#include "schema_table/schema_alter_ctx/TableRenameContext.h"

#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"

#include "schema_table/table/CdbTableIndex.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"

#include "engine/CdbOid.h"

#include "lang_sql/sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterRenameColumnCommand.h"
#include "lang_sql/sql_ddl_alter_modify/AlterModifyCommand.h"

#include "lang_sql/sql_ddl_alter/AlterAddIndexCommand.h"
#include "lang_sql/sql_ddl_alter/AlterDropIndexCommand.h"
#include "lang_sql/sql_ddl_alter/AlterAddColumnCommand.h"
#include "lang_sql/sql_ddl_alter/AlterDropColumnCommand.h"

#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"

using namespace alinous;

namespace codablecash {

SchemaAlterCommandsHandler::SchemaAlterCommandsHandler(SchemaManager* schemaManager) {
	this->schemaManager = schemaManager;
}

SchemaAlterCommandsHandler::~SchemaAlterCommandsHandler() {
	this->schemaManager = nullptr;
}

void SchemaAlterCommandsHandler::handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd) {
	const AlterAddIndexCommand* command = cmd->getCommand();

	CdbTable* table = findTableFromCommand(cmd);

	uint64_t newOid = this->schemaManager->root->newSchemaObjectId();
	CdbTableIndex* newIndex = new CdbTableIndex(newOid);

	const UnicodeString* indexName = command->getName();
	newIndex->setName(new UnicodeString(indexName));

	const ArrayList<UnicodeString>* colList = command->getList();
	int maxLoop = colList->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* colstr = colList->get(i);

		const CdbTableColumn* col = table->getColumn(colstr);
		assert(col != nullptr);

		newIndex->addColumn(col);
	}

	newIndex->setUnique(command->isUnique());
	table->addIndex(newIndex);

	this->schemaManager->fireOnAddIndex(table, newIndex);

	// save
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
	const AlterDropIndexCommand* command = cmd->getCommand();

	CdbTable* table = findTableFromCommand(cmd);

	const UnicodeString* indexName = command->getName();
	CdbTableIndex* removalIndex = table->getIndexByName(indexName); __STP(removalIndex);
	assert(removalIndex != nullptr);

	table->removeIndex(removalIndex);

	this->schemaManager->fireOnDropIndex(table, removalIndex);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd) {
	AlterAddColumnCommand* command = cmd->getCommand();

	CdbTable* table = findTableFromCommand(cmd);

	const DdlColumnDescriptor* columnDesc = command->getColumnDescriptor();
	const ColumnTypeDescriptor* typeDesc = columnDesc->getTypeDesc();

	uint64_t newOid = this->schemaManager->root->newSchemaObjectId();
	const UnicodeString* colName = columnDesc->getName();
	uint8_t cdbType = typeDesc->toCdbValueType();
	int colLength = command->getLengthValue();
	bool notnull = columnDesc->isNotNull();
	bool unique = columnDesc->isUnique();
	const UnicodeString* defValue = command->getDefaultValueStr();

	table->addColumn(newOid, colName, cdbType, colLength, notnull, unique, defValue);

	CdbTableColumn* newColumn = table->getColumn(colName);
	CdbTableIndex* newUniqueIndex = nullptr;
	if(newColumn->isUnique()){
		uint64_t newIdxOid = this->schemaManager->root->newSchemaObjectId();
		newUniqueIndex = new CdbTableIndex(newIdxOid);

		UnicodeString* indexName = CdbTableIndex::createUniqueKeyIndexName(table, newColumn->getName());
		newUniqueIndex->setName(indexName);
		newUniqueIndex->addColumn(newColumn);
		newUniqueIndex->setUnique(true);
		newUniqueIndex->setPrimaryKey(false);

		table->addIndex(newUniqueIndex);
	}

	this->schemaManager->fireOnAddColumn(table, newColumn, newUniqueIndex);

	// save
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
	const AlterDropColumnCommand* command = cmd->getCommand();

	CdbTable* table = findTableFromCommand(cmd);

	const UnicodeString* columnName = command->getName();

	ArrayList<CdbTableIndex>* removalIndexes = table->removeIndexesUsingColumn(columnName); __STP(removalIndexes);
	removalIndexes->setDeleteOnExit();

	CdbTableColumn* removalColumn = table->removeColumn(columnName); __STP(removalColumn);

	this->schemaManager->fireOnDropColumn(table, removalColumn, removalIndexes);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	const AlterAddPrimaryKeyCommand* command = cmd->getCommand();
	const ArrayList<UnicodeString>* collist = command->getColumns();

	const CdbTableIndex* newidx = table->setPrimaryKeys(collist);

	if(newidx != nullptr){
		this->schemaManager->fireOnAddPrimaryKey(table, newidx);
	}

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	CdbTableIndex* primaryKey = table->getPrimaryKey();
	StackRelease<CdbTableIndex> stPrimaryKey(primaryKey);

	assert(primaryKey != nullptr);

	// check unique of column on length == 1
	if(primaryKey->getColumnLength() == 1 && primaryKey->getColumnAt(0)->isUnique()){
		primaryKey->setPrimaryKey(false);
		stPrimaryKey.cancel();

		// upgrade
		this->schemaManager->root->upgradeSchemaObjectVersionId();
		this->schemaManager->save();
		return;
	}

	table->removeIndex(primaryKey);

	this->schemaManager->fireOnDropPrimaryKey(table, primaryKey);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableModify(const AlterModifyCommandLog* cmd) {
	CdbTable* table = this->schemaManager->findTableFromCommand(cmd);

	const AlterModifyCommand* modifyCommand = cmd->getCommand();

	const DdlColumnDescriptor* newdesc = modifyCommand->getColumnDescriptor();

	CdbTableColumn* col = table->getColumn(newdesc->getName());
	if(col == nullptr){
		throw new CdbException(L"Column does not exists.", __FILE__, __LINE__);
	}

	const UnicodeString* defaultStr = cmd->getCommand()->getDefaultValueStr();

	ColumnModifyContext* context = col->createModifyContextwithChange(modifyCommand, defaultStr); __STP(context);
	context->setColumn(col);

	// convert default
	context->analyze();

	handleUniqueIndexOnModify(table, context);

	// update storage
	this->schemaManager->fireOnAlterModify(table, context);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleUniqueIndexOnModify(CdbTable* table,	ColumnModifyContext* ctx) {
	ColumnModifyContext::UniqueChage change = ctx->getUniqueChange();

	if(change == ColumnModifyContext::UniqueChage::TO_NOT_UNIQUE){
		handleToNotUnique(table, ctx);
	}
	else if(change == ColumnModifyContext::UniqueChage::TO_UNIQUE){
		handleToUnique(table, ctx);
	}
}

void SchemaAlterCommandsHandler::handleToNotUnique(CdbTable* table,	ColumnModifyContext* ctx) {
	CdbTableColumn* col = ctx->getColumn();
	const CdbOid* colOid = col->getOid();

	ArrayList<const CdbOid> oidlist;
	oidlist.addElement(colOid);

	CdbTableIndex* index = table->getIndexByColumnOidsStrict(&oidlist, true);
	if(index == nullptr || index->isPrimaryKey()){ // leave primary key
		if(index != nullptr){
			index->setUnique(false);
		}
		return;
	}

	ctx->setRemovalIndex(index);
	table->removeIndex(index);
}

void SchemaAlterCommandsHandler::handleToUnique(CdbTable* table, ColumnModifyContext* ctx) {
	CdbTableColumn* col = ctx->getColumn();
	const CdbOid* colOid = col->getOid();

	// already has primary key
	if(table->hasSinglePrimaryKeyColumn(colOid)){
		CdbTableIndex* idx = table->getPrimaryKey();
		idx->setUnique(true);
		return;
	}

	// already has not-unique index
	ArrayList<const CdbOid> oidlist;
	oidlist.addElement(colOid);
	CdbTableIndex* idx = table->getIndexByColumnOidsStrict(&oidlist, false);
	if(idx != nullptr){
		idx->setUnique(true);
		return;
	}

	uint64_t newOid = this->schemaManager->root->newSchemaObjectId();
	CdbTableIndex* newIndex = new CdbTableIndex(newOid);
	ctx->setNewIndex(newIndex);

	UnicodeString* indexName = CdbTableIndex::createUniqueKeyIndexName(table, col->getName());
	newIndex->setName(indexName);
	newIndex->addColumn(col);
	newIndex->setUnique(true);

	table->addIndex(newIndex);
}

void SchemaAlterCommandsHandler::handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd) {
	const AlterRenameColumnCommand* command = cmd->getCommand();
	const UnicodeString* lastName = command->getLastName();
	const UnicodeString* newName = command->getNewName();

	CdbTable* table = findTableFromCommand(cmd);
	table->renameColumn(lastName, newName);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	TableRenameContext context;
	context.init(cmd, this->schemaManager, nullptr);

	this->schemaManager->fireOnRenameTable(table, &context);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

CdbTable* SchemaAlterCommandsHandler::findTableFromCommand(const AbstractAlterCommandLog* cmdlog) {
	const TableIdentifier* tableId = cmdlog->getTableId();

	const UnicodeString* schema = tableId->getSchema();
	const UnicodeString* tableName = tableId->getTableName();

	CdbTable* table = this->schemaManager->getTable(schema, tableName);

	return table;
}

} /* namespace codablecash */
