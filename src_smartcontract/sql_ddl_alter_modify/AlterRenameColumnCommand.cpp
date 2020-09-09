/*
 * AlterRenameColumnCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameColumnCommand.h"

namespace alinous {

AlterRenameColumnCommand::AlterRenameColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_COLUMN) {

}

AlterRenameColumnCommand::~AlterRenameColumnCommand() {

}

int AlterRenameColumnCommand::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterRenameColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
