/*
 * AlterRenameTableCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

namespace alinous {

AlterRenameTableCommand::AlterRenameTableCommand(const AlterRenameTableCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_TABLE){
	this->newName = new UnicodeString(inst.newName);
}


AlterRenameTableCommand::AlterRenameTableCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_TABLE) {
	this->newName = nullptr;
}

AlterRenameTableCommand::~AlterRenameTableCommand() {
	delete this->newName;
}

void AlterRenameTableCommand::setNewName(UnicodeString* name) noexcept {
	this->newName = name;
}

int AlterRenameTableCommand::binarySize() const {
	checkNotNull(this->newName);

	int total = sizeof(uint16_t);
	total += stringSize(this->newName);

	return total;
}

void AlterRenameTableCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->newName);

	out->putShort(CodeElement::DDL_ALTER_RENAME_TABLE);
	putString(out, this->newName);
}

void AlterRenameTableCommand::fromBinary(ByteBuffer* in) {
	this->newName = getString(in);
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

void AlterRenameTableCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log) {
}


} /* namespace alinous */
