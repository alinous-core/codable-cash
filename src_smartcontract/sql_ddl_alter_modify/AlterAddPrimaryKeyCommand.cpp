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

	int maxLoop = this->list.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		total += stringSize(col);
	}

	return total;
}

void AlterAddPrimaryKeyCommand::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = this->list.get(i);
		putString(out, col);
	}
}

void AlterAddPrimaryKeyCommand::fromBinary(ByteBuffer* in) {
	int maxLoop =in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* col = getString(in);
		addColumn(col);
	}
}

AbstractDdlLog* AlterAddPrimaryKeyCommand::getCommandLog() {
}


} /* namespace alinous */
