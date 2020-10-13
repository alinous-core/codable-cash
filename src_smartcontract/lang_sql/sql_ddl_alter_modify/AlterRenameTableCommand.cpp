/*
 * AlterRenameTableCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "base/UnicodeString.h"

#include "trx/transaction_log_alter_modify/AlterRenameTableCommandLog.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"

#include "engine/CodableDatabase.h"

#include "schema_table/schema/SchemaManager.h"

#include "vm/VirtualMachine.h"

#include "schema_table/schema_alter_ctx/TableRenameContext.h"

namespace alinous {

AlterRenameTableCommand::AlterRenameTableCommand(const AlterRenameTableCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_TABLE){
	this->newName = new TableIdentifier(*inst.newName);
}


AlterRenameTableCommand::AlterRenameTableCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_TABLE) {
	this->newName = nullptr;
}

AlterRenameTableCommand::~AlterRenameTableCommand() {
	delete this->newName;
}

void AlterRenameTableCommand::setNewName(TableIdentifier* name) noexcept {
	this->newName = name;
}

int AlterRenameTableCommand::binarySize() const {
	checkNotNull(this->newName);

	int total = sizeof(uint16_t);
	total += this->newName->binarySize();

	return total;
}

void AlterRenameTableCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->newName);

	out->putShort(CodeElement::DDL_ALTER_RENAME_TABLE);
	this->newName->toBinary(out);
}

void AlterRenameTableCommand::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_TABLE_ID);

	this->newName = dynamic_cast<TableIdentifier*>(element);
}

AbstractAlterCommandLog* AlterRenameTableCommand::getCommandLog() {
	AlterRenameTableCommandLog* log = new AlterRenameTableCommandLog();
	log->setCommand(new AlterRenameTableCommand(*this));

	return log;
}

void AlterRenameTableCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterRenameTableCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterRenameTableCommand::analyze(AnalyzeContext* actx) {
}

void AlterRenameTableCommand::inputDefaultSchema(const UnicodeString* defaultSchema) {
	this->newName->inputDefaultSchema(defaultSchema);
}

void AlterRenameTableCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId) {
	AlterRenameTableCommandLog* renameTableLog = dynamic_cast<AlterRenameTableCommandLog*>(log);

	CodableDatabase* db = vm->getDb();

	TableRenameContext context;

	const UnicodeString* defaultSchema = vm->getCurrentSchema();
	context.init(renameTableLog, db->getSchemaManager(), defaultSchema); // includes validation process

	context.validate(db->getSchemaManager());

	renameTableLog->inputDefaultSchema(defaultSchema);
}


} /* namespace alinous */
