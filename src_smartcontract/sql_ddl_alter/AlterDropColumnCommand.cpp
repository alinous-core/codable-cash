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
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void AlterDropColumnCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_DROP_COLUMN);
	putString(out, this->name);
}

void AlterDropColumnCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}

AbstractDdlLog* AlterDropColumnCommand::getCommandLog() {
}

} /* namespace alinous */
