/*
 * AlterDropPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"

#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"

#include "vm/VirtualMachine.h"

#include "sql_join_parts/TableIdentifier.h"

#include "table/CdbTable.h"


namespace alinous {

AlterDropPrimaryKeyCommand::AlterDropPrimaryKeyCommand(const AlterDropPrimaryKeyCommand& inst)
	: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY) {
}

AlterDropPrimaryKeyCommand::AlterDropPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY) {

}

AlterDropPrimaryKeyCommand::~AlterDropPrimaryKeyCommand() {

}

int AlterDropPrimaryKeyCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropPrimaryKeyCommand::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY);
}

void AlterDropPrimaryKeyCommand::fromBinary(ByteBuffer* in) {
}

AbstractAlterCommandLog* AlterDropPrimaryKeyCommand::getCommandLog() {
	AlterDropPrimaryKeyCommandLog* log = new AlterDropPrimaryKeyCommandLog();
	log->setCommand(new AlterDropPrimaryKeyCommand(*this));

	return log;
}

void AlterDropPrimaryKeyCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterDropPrimaryKeyCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterDropPrimaryKeyCommand::analyze(AnalyzeContext* actx) {
}

void AlterDropPrimaryKeyCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterDropPrimaryKeyCommandLog* dropPrimaryKeyLog = dynamic_cast<AlterDropPrimaryKeyCommandLog*>(log);
	const AlterDropPrimaryKeyCommand* command = dropPrimaryKeyLog->getCommand();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	tableId->inputDefaultSchema(defaultSchema);

	CdbTable* table = schemaManager->getTable(tableId, nullptr); // throws if Table does not exists;

	CdbTableIndex* pkey = table->getPrimaryKey();
	if(pkey == nullptr){
		throw new CdbException(L"Primary key does not exists", __FILE__, __LINE__);
	}
}



} /* namespace alinous */
