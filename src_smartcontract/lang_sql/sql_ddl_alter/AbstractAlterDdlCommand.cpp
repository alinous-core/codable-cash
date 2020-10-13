/*
 * AbstractAlterDdlCommand.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl_alter/AbstractAlterDdlCommand.h"

#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"

#include "base/StackRelease.h"

#include "base_io/ByteBuffer.h"


namespace alinous {

AbstractAlterDdlCommand::AbstractAlterDdlCommand(short kind) : CodeElement(kind) {

}

AbstractAlterDdlCommand::~AbstractAlterDdlCommand() {

}

} /* namespace alinous */
