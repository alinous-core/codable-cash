/*
 * AlterModifyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

namespace alinous {

AlterModifyCommand::AlterModifyCommand(const AlterModifyCommand& inst) : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_MODIFY) {
	this->columnDescriptor = copyColumnDescriptor(inst.columnDescriptor);
}


AlterModifyCommand::AlterModifyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_MODIFY) {
	this->columnDescriptor = nullptr;
}

AlterModifyCommand::~AlterModifyCommand() {
	delete this->columnDescriptor;
}

void AlterModifyCommand::setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept {
	this->columnDescriptor = columnDescriptor;
}

int AlterModifyCommand::binarySize() const {
	checkNotNull(this->columnDescriptor);

	int total = sizeof(uint16_t);
	total += this->columnDescriptor->binarySize();

	return total;
}

void AlterModifyCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnDescriptor);

	out->putShort(CodeElement::DDL_ALTER_MODIFY);
	this->columnDescriptor->toBinary(out);
}

void AlterModifyCommand::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::DDL_COLMUN_DESC);

	this->columnDescriptor = dynamic_cast<DdlColumnDescriptor*>(element);
}

AbstractDdlLog* AlterModifyCommand::getCommandLog() {
	AlterModifyCommandLog* log = new AlterModifyCommandLog();
	log->setCommand(new AlterModifyCommand(*this));

	return log;
}


} /* namespace alinous */
