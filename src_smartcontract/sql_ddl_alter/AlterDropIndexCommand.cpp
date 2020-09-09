/*
 * AlterDropIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropIndexCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

AlterDropIndexCommand::AlterDropIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_INDEX) {
	this->name = nullptr;
}

AlterDropIndexCommand::~AlterDropIndexCommand() {
	delete this->name;
}

void AlterDropIndexCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int AlterDropIndexCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropIndexCommand::toBinary(ByteBuffer* out) {
}

void AlterDropIndexCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
