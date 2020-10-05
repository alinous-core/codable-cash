/*
 * TableRenameContext.cpp
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#include "schema_alter_ctx/TableRenameContext.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "engine/CodableDatabase.h"

#include "schema/SchemaManager.h"

#include "sql_join_parts/TableIdentifier.h"

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

namespace codablecash {

TableRenameContext::TableRenameContext() {
	this->srcSchema = nullptr;
	this->dstSchema = nullptr;
	this->srcTable = nullptr;
	this->dstTable = nullptr;

	this->table = nullptr;
}

TableRenameContext::~TableRenameContext() {
	delete this->srcSchema;
	delete this->dstSchema;
	delete this->srcTable;
	delete this->dstTable;

	this->table = nullptr;
}

void TableRenameContext::init(const AlterRenameTableCommandLog* renameTableLog, CodableDatabase* db, const UnicodeString* defaultSchema) {
	SchemaManager* schemaManamger = db->getSchemaManager();

	const TableIdentifier* srcTable = renameTableLog->getTableId();

	const UnicodeString* s = srcTable->getSchema();
	this->srcSchema = s != nullptr ? new UnicodeString(s) : new UnicodeString(defaultSchema);
	this->srcTable = new UnicodeString(srcTable->getTableName());

	const AlterRenameTableCommand* cmd = renameTableLog->getCommand();
	const TableIdentifier* destTable = cmd->getNewName();

	s = destTable->getSchema();
	this->dstSchema = s != nullptr ? new UnicodeString(s) : new UnicodeString(defaultSchema);
	this->dstTable = new UnicodeString(destTable->getTableName());

	this->table = schemaManamger->getTable(srcTable, defaultSchema);
}

} /* namespace codablecash */
