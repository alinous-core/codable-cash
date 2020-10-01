/*
 * AlterAddIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddIndexCommand.h"

#include "base/UnicodeString.h"

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

namespace alinous {

AlterAddIndexCommand::AlterAddIndexCommand(const AlterAddIndexCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {
	this->name = new UnicodeString(inst.name);
	this->unique = inst.unique;

	int maxLoop = inst.list.size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* col = inst.list.get(i);

		addColumn(new UnicodeString(col));
	}
}

AlterAddIndexCommand::AlterAddIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {
	this->name = nullptr;
	this->unique = false;
}

AlterAddIndexCommand::~AlterAddIndexCommand() {
	delete this->name;
	this->list.deleteElements();
}

void AlterAddIndexCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void AlterAddIndexCommand::addColumn(UnicodeString* colName) noexcept {
	this->list.addElement(colName);
}

int AlterAddIndexCommand::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);
	total += sizeof(uint8_t);

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		total += stringSize(col);
	}

	return total;
}

void AlterAddIndexCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_ADD_INDEX);
	putString(out, this->name);
	out->put(this->unique ? 1 : 0);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		putString(out, col);
	}
}

void AlterAddIndexCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	uint8_t bl = in->get();
	this->unique = (bl >= 1);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = getString(in);
		addColumn(col);
	}
}

AbstractAlterCommandLog* AlterAddIndexCommand::getCommandLog() {
	AlterAddIndexCommandLog* log = new AlterAddIndexCommandLog();
	log->setCommand(new AlterAddIndexCommand(*this));

	return log;
}

void AlterAddIndexCommand::preAnalyze(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::analyze(AnalyzeContext* actx) {
}

void AlterAddIndexCommand::interpret(VirtualMachine* vm, AbstractAlterCommandLog* log) {
}

} /* namespace alinous */
