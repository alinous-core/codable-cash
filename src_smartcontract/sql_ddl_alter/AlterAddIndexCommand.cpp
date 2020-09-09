/*
 * AlterAddIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddIndexCommand.h"

#include "base/UnicodeString.h"

namespace alinous {

AlterAddIndexCommand::AlterAddIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {
	this->name = nullptr;
}

AlterAddIndexCommand::~AlterAddIndexCommand() {
	delete this->name;
	this->list.deleteElements();
}

void AlterAddIndexCommand::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void AlterAddIndexCommand::addColumn(UnicodeString* colName) noexcept {
	this->list.addElement(colName);
}

int AlterAddIndexCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterAddIndexCommand::toBinary(ByteBuffer* out) {
}

void AlterAddIndexCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
