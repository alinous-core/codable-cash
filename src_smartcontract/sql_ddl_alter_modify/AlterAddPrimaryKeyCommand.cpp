/*
 * AlterAddPrimaryKeyCommand.cpp
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#include "sql_ddl_alter_modify/AlterAddPrimaryKeyCommand.h"

namespace alinous {

AlterAddPrimaryKeyCommand::AlterAddPrimaryKeyCommand() : AbstractAlterDdlCommand(CodeElement::DDL_ALTER_ADD_PRIMARY_KEY){
}

AlterAddPrimaryKeyCommand::~AlterAddPrimaryKeyCommand() {

}

} /* namespace alinous */
