/*
 * AlterAddColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddColumnCommand.h"

namespace alinous {

AlterAddColumnCommand::AlterAddColumnCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_COLUMN) {

}

AlterAddColumnCommand::~AlterAddColumnCommand() {

}

int AlterAddColumnCommand::binarySize() const {
}

void AlterAddColumnCommand::toBinary(ByteBuffer* out) {
}

void AlterAddColumnCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
