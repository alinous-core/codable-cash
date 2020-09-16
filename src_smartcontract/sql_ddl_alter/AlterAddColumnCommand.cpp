/*
 * AlterAddColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddColumnCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "transaction_log_alter/AlterAddColumnCommandLog.h"

namespace alinous {

AlterAddColumnCommand::AlterAddColumnCommand(const AlterAddColumnCommand& inst)
				: AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_COLUMN) {
	this->columnDescriptor = copyColumnDescriptor(inst.columnDescriptor);
}

AlterAddColumnCommand::AlterAddColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_COLUMN) {
	this->columnDescriptor = nullptr;
}

AlterAddColumnCommand::~AlterAddColumnCommand() {
	delete this->columnDescriptor;
}

void AlterAddColumnCommand::setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept {
	this->columnDescriptor = columnDescriptor;
}

int AlterAddColumnCommand::binarySize() const {
	checkNotNull(this->columnDescriptor);

	int total = sizeof(uint16_t);
	total += this->columnDescriptor->binarySize();

	return total;
}

void AlterAddColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnDescriptor);

	out->putShort(CodeElement::DDL_ALTER_ADD_COLUMN);
	this->columnDescriptor->toBinary(out);
}

void AlterAddColumnCommand::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::DDL_COLMUN_DESC);

	this->columnDescriptor = dynamic_cast<DdlColumnDescriptor*>(element);
}

AbstractAlterCommandLog* AlterAddColumnCommand::getCommandLog() {
	AlterAddColumnCommandLog* log = new AlterAddColumnCommandLog();
	log->setCommand(new AlterAddColumnCommand(*this));

	return log;
}

} /* namespace alinous */
