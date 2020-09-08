/*
 * AlterAddIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddIndexCommand.h"

namespace alinous {

AlterAddIndexCommand::AlterAddIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_INDEX) {

}

AlterAddIndexCommand::~AlterAddIndexCommand() {

}

int AlterAddIndexCommand::binarySize() const {
}

void AlterAddIndexCommand::toBinary(ByteBuffer* out) {
}

void AlterAddIndexCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
