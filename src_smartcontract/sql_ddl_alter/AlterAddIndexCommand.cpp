/*
 * AlterAddIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterAddIndexCommand.h"

namespace alinous {

AlterAddIndexCommand::AlterAddIndexCommand(short kind) : AbstractAlterDdlCommand(kind) {

}

AlterAddIndexCommand::~AlterAddIndexCommand() {

}

} /* namespace alinous */
