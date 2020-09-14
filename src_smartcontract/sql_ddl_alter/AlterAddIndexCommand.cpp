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
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		total += stringSize(col);
	}

	return total;
}

void AlterAddIndexCommand::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_ALTER_ADD_INDEX);
	putString(out, this->name);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		putString(out, col);
	}
}

void AlterAddIndexCommand::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = getString(in);
		addColumn(col);
	}
}

AbstractDdlLog* AlterAddIndexCommand::getCommandLog() {
}

} /* namespace alinous */
