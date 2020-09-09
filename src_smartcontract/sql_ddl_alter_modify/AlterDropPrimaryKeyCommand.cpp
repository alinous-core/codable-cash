/*
 * AlterDropPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterDropPrimaryKeyCommand.h"

namespace alinous {

AlterDropPrimaryKeyCommand::AlterDropPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_DROP_PRIMARY_KEY) {

}

AlterDropPrimaryKeyCommand::~AlterDropPrimaryKeyCommand() {

}

} /* namespace alinous */
