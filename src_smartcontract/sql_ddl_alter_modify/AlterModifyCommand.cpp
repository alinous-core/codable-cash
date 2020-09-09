/*
 * AlterModifyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterModifyCommand.h"

namespace alinous {

AlterModifyCommand::AlterModifyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_MODIFY) {

}

AlterModifyCommand::~AlterModifyCommand() {

}

int AlterModifyCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterModifyCommand::toBinary(ByteBuffer* out) {
}

void AlterModifyCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
