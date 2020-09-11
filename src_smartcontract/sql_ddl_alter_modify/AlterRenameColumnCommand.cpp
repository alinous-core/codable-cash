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
	checkNotNull(this->lastName);
	checkNotNull(this->newName);

	int total = sizeof(uint16_t);
	total += stringSize(this->lastName);
	total += stringSize(this->newName);

	return total;
}

void AlterRenameColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->lastName);
	checkNotNull(this->newName);

	out->putShort(CodeElement::DDL_ALTER_RENAME_COLUMN);
	putString(out, this->lastName);
	putString(out, this->newName);
}

void AlterRenameColumnCommand::fromBinary(ByteBuffer* in) {
	this->lastName = getString(in);
	this->newName = getString(in);
}

} /* namespace alinous */
