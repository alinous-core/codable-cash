/*
 * AlterRenameTableCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

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
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameTableCommand::toBinary(ByteBuffer* out) {
}

void AlterRenameTableCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
