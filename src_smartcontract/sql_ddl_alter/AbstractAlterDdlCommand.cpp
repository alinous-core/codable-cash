/*
 * AbstractAlterDdlCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

AbstractAlterDdlCommand::AbstractAlterDdlCommand(short kind) : CodeElement(kind) {

}

AbstractAlterDdlCommand::~AbstractAlterDdlCommand() {

}

} /* namespace alinous */
