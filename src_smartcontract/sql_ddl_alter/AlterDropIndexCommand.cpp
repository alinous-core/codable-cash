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
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void AlterDropIndexCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_DROP_INDEX);
	putString(out, this->name);
}

void AlterDropIndexCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}

} /* namespace alinous */
