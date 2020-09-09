/*
 * AlterAddColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddColumnCommand.h"

#include "sql_ddl/DdlColumnDescriptor.h"

namespace alinous {

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
	int total = sizeof(uint16_t);

	return total;
}

void AlterAddColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterAddColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
