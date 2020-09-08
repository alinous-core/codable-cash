/*
 * AlterDropIndexCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AlterDropIndexCommand.h"

namespace alinous {

AlterDropIndexCommand::AlterDropIndexCommand(short kind) : AbstractAlterDdlCommand(kind) {

}

AlterDropIndexCommand::~AlterDropIndexCommand() {

}

} /* namespace alinous */
