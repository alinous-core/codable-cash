/*
 * AlterDropIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropIndexCommand.h"

namespace alinous {

AlterDropIndexCommand::AlterDropIndexCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_INDEX) {

}

AlterDropIndexCommand::~AlterDropIndexCommand() {

}

int AlterDropIndexCommand::binarySize() const {
}

void AlterDropIndexCommand::toBinary(ByteBuffer* out) {
}

void AlterDropIndexCommand::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
