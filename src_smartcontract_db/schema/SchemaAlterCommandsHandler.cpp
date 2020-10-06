/*
 * SchemaAlterCommandsHandler.cpp
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#include "schema/SchemaAlterCommandsHandler.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "transaction_log_alter/AlterAddIndexCommandLog.h"
#include "transaction_log_alter/AlterAddColumnCommandLog.h"
#include "transaction_log_alter/AlterDropIndexCommandLog.h"
#include "transaction_log_alter/AlterDropColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterModifyCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "schema/SchemaManager.h"
#include "schema/SchemaRoot.h"

#include "schema_alter_ctx/ColumnModifyContext.h"
#include "schema_alter_ctx/TableRenameContext.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "table/CdbTableIndex.h"

#include "sql_join_parts/TableIdentifier.h"

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

namespace codablecash {

SchemaAlterCommandsHandler::SchemaAlterCommandsHandler(SchemaManager* schemaManager) {
	this->schemaManager = schemaManager;
}

SchemaAlterCommandsHandler::~SchemaAlterCommandsHandler() {
	this->schemaManager = nullptr;
}

void SchemaAlterCommandsHandler::handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// TODO: alter add

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
	CdbTable* table = findTableFromCommand(cmd);

	CdbTableIndex* primaryKey = table->getPrimaryKey();
	StackRelease<CdbTableIndex> stPrimaryKey(primaryKey);

	if(primaryKey == nullptr){
		return;
	}

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

	const UnicodeString* defaultStr = cmd->getDefaultValueStr();

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

	CdbTableIndex* index = table->getUniqueIndexByColumnOid(colOid);
	if(index == nullptr || index->isPrimaryKey()){ // primary key support unique
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
	// TODO: rename exrcute

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
