/*
 * AlterAddPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

AlterAddPrimaryKeyCommand::AlterAddPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY){
}

AlterAddPrimaryKeyCommand::~AlterAddPrimaryKeyCommand() {
	this->list.deleteElements();
}

void AlterAddPrimaryKeyCommand::addColumn(UnicodeString* column) noexcept {
	this->list.addElement(column);
}

int AlterAddPrimaryKeyCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterAddPrimaryKeyCommand::toBinary(ByteBuffer* out) {
}

void AlterAddPrimaryKeyCommand::fromBinary(ByteBuffer* in) {
}


} /* namespace alinous */
