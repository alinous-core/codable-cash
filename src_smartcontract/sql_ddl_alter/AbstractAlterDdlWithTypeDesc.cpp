/*
 * AbstractAlterDdlWithTypeDesc.cpp
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#include "sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

namespace alinous {

AbstractAlterDdlWithTypeDesc::AbstractAlterDdlWithTypeDesc(short kind) : AbstractAlterDdlCommand(kind) {

}

AbstractAlterDdlWithTypeDesc::~AbstractAlterDdlWithTypeDesc() {

}

} /* namespace alinous */
