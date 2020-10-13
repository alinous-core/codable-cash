/*
 * TableRenameContext.cpp
 *
 *  Created on: 2020/10/05
 *      Author: iizuka
 */

#include "schema_table/schema_alter_ctx/TableRenameContext.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema_table/schema/SchemaManager.h"
#include "schema_table/schema/Schema.h"

#include "sql_join_parts/TableIdentifier.h"

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "schema_table/table/CdbTable.h"


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

void TableRenameContext::init(const AlterRenameTableCommandLog* renameTableLog, SchemaManager* schemaManamger, const UnicodeString* defaultSchema) {
	const TableIdentifier* srcTable = renameTableLog->getTableId();

	const UnicodeString* s = srcTable->getSchema();
	this->srcSchema = s != nullptr ? new UnicodeString(s) : new UnicodeString(defaultSchema);
	this->srcTable = new UnicodeString(srcTable->getTableName());

	const AlterRenameTableCommand* cmd = renameTableLog->getCommand();
	const TableIdentifier* destTable = cmd->getNewName();

	s = destTable->getSchema();
	this->dstSchema = s != nullptr ? new UnicodeString(s) : new UnicodeString(defaultSchema);
	this->dstTable = new UnicodeString(destTable->getTableName());

	this->table = schemaManamger->getTable(srcTable, defaultSchema); // throws CdbException if not exists
}

void TableRenameContext::validate(SchemaManager* schemaManamger) {
	if(schemaManamger->hasTable(this->dstSchema, this->dstTable)){
		throw new CdbException(L"", __FILE__, __LINE__);
	}
}

void TableRenameContext::commitSchemaDir(SchemaManager* schemaManamger) {
	if(isSchemaChanged()){
		Schema* sc = schemaManamger->getSchema(this->dstSchema);
		if(sc == nullptr){
			schemaManamger->createSchema(this->dstSchema);
		}
	}
}

void TableRenameContext::commit(SchemaManager* schemaManamger) {
	if(isSchemaChanged()){
		Schema* lastScema = schemaManamger->getSchema(this->srcSchema);
		Schema* sc = schemaManamger->getSchema(this->dstSchema);

		assert(sc != nullptr);

		// move schema
		lastScema->removeTable(this->srcTable);

		this->table->setName(new UnicodeString(this->dstTable));
		sc->addTable(this->table);
	}
	else {
		Schema* sc = schemaManamger->getSchema(this->srcSchema);
		sc->renameTable(this->srcTable, this->dstTable);
	}
}

bool TableRenameContext::isSchemaChanged() const noexcept {
	return !this->dstSchema->equals(this->srcSchema);
}

} /* namespace codablecash */
