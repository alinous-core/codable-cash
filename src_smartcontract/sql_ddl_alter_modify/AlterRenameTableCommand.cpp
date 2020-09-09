/*
 * AlterRenameTableCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterRenameTableCommand.h"

namespace alinous {

AlterRenameTableCommand::AlterRenameTableCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_RENAME_TABLE) {

}

AlterRenameTableCommand::~AlterRenameTableCommand() {

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
