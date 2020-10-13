/*
 * AlterDropColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropColumnCommand.h"

#include "base/UnicodeString.h"

#include "trx/transaction_log_alter/AlterDropColumnCommandLog.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "engine/CodableDatabase.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "engine/CdbException.h"

namespace alinous {

AlterDropColumnCommand::AlterDropColumnCommand(const AlterDropColumnCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_COLUMN){
	this->name = new UnicodeString(inst.name);
}

AlterDropColumnCommand::AlterDropColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_COLUMN) {
	this->name = nullptr;
}

AlterDropColumnCommand::~AlterDropColumnCommand() {
	delete this->name;
}

void AlterDropColumnCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int AlterDropColumnCommand::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void AlterDropColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_DROP_COLUMN);
	putString(out, this->name);
}

void AlterDropColumnCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}

AbstractAlterCommandLog* AlterDropColumnCommand::getCommandLog() {
	AlterDropColumnCommandLog* log = new AlterDropColumnCommandLog();
	log->setCommand(new AlterDropColumnCommand(*this));

	return log;
}

void AlterDropColumnCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterDropColumnCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterDropColumnCommand::analyze(AnalyzeContext* actx) {
}

void AlterDropColumnCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterDropColumnCommandLog* thisLog = dynamic_cast<AlterDropColumnCommandLog*>(log);
	const AlterDropColumnCommand* command = thisLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	const UnicodeString* colName = command->getName();
	CdbTableColumn* col = table->getColumn(colName);
	if(col == nullptr){
		throw new CdbException(L"Column does not exist", __FILE__, __LINE__);
	}

	CdbTableIndex* primaryKey = table->getPrimaryKey();
	if(primaryKey->hasColumnOid(col->getOid())){
		throw new CdbException(L"Can not delete columns used in Primary Key.", __FILE__, __LINE__);
	}
}

} /* namespace alinous */
