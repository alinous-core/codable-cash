/*
 * AlterModifyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"

namespace alinous {

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
	int total = sizeof(uint16_t);

	return total;
}

void AlterModifyCommand::toBinary(ByteBuffer* out) {
}

void AlterModifyCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
