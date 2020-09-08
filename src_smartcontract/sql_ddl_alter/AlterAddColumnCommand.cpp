/*
 * AlterAddColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddColumnCommand.h"

namespace alinous {

AlterAddColumnCommand::AlterAddColumnCommand(short kind) : AbstractAlterDdlCommand(kind) {

}

AlterAddColumnCommand::~AlterAddColumnCommand() {

}

} /* namespace alinous */
