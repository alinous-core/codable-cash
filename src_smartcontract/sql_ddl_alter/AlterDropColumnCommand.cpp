/*
 * AlterDropColumnCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropColumnCommand.h"

namespace alinous {

AlterDropColumnCommand::AlterDropColumnCommand(short kind) : AbstractAlterDdlCommand(kind) {

}

AlterDropColumnCommand::~AlterDropColumnCommand() {

}

} /* namespace alinous */
