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

#include "sql_ddl/DdlColumnDescriptor.h"

#include "sql_ddl_alter_modify/AlterModifyCommand.h"


namespace codablecash {

SchemaAlterCommandsHandler::SchemaAlterCommandsHandler(SchemaManager* schemaManager) {
	this->schemaManager = schemaManager;
}

SchemaAlterCommandsHandler::~SchemaAlterCommandsHandler() {
	this->schemaManager = nullptr;
}

void SchemaAlterCommandsHandler::handleAlterTableAddIndex(const AlterAddIndexCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableAddColumn(const AlterAddColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropIndex(const AlterDropIndexCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropColumn(const AlterDropColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableAddPrimaryKey(const AlterAddPrimaryKeyCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableDropPrimaryKey(const AlterDropPrimaryKeyCommandLog* cmd) {
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

	this->schemaManager->handleUniqueIndexOnModify(table, context);

	// update storage
	this->schemaManager->fireOnAlterModify(table, context);

	// upgrade
	this->schemaManager->root->upgradeSchemaObjectVersionId();
	this->schemaManager->save();
}

void SchemaAlterCommandsHandler::handleAlterTableRenameColumn(const AlterRenameColumnCommandLog* cmd) {
}

void SchemaAlterCommandsHandler::handleAlterTableRenameTable(const AlterRenameTableCommandLog* cmd) {
}

} /* namespace codablecash */
