/*
 * AlterDropColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropColumnCommand.h"

namespace alinous {

AlterDropColumnCommand::AlterDropColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_COLUMN) {

}

AlterDropColumnCommand::~AlterDropColumnCommand() {

}

int AlterDropColumnCommand::binarySize() const {
}

void AlterDropColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterDropColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
