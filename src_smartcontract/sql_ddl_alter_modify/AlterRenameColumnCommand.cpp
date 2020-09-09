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

} /* namespace alinous */
