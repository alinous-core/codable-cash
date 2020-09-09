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

} /* namespace alinous */
