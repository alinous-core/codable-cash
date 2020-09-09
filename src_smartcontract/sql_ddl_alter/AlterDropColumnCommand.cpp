/*
 * AlterDropColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropColumnCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

AlterDropColumnCommand::AlterDropColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_COLUMN) {
	this->name = nullptr;
}

AlterDropColumnCommand::~AlterDropColumnCommand() {
	delete this->name;
}

void AlterDropColumnCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int AlterDropColumnCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterDropColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
