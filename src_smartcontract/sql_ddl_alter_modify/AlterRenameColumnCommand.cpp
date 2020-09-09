/*
 * AlterRenameColumnCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

AlterRenameColumnCommand::AlterRenameColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_COLUMN) {
	this->lastName = nullptr;
	this->newName = nullptr;
}

AlterRenameColumnCommand::~AlterRenameColumnCommand() {
	delete this->lastName;
	delete this->newName;
}

void AlterRenameColumnCommand::setLastName(UnicodeString* name) noexcept {
	this->lastName = name;
}

void AlterRenameColumnCommand::setNewName(UnicodeString* name) noexcept {
	this->newName = name;
}

int AlterRenameColumnCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterRenameColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
