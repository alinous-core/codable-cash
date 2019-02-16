/*
 * CreateTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/CreateTableStatement.h"

namespace alinous {

CreateTableStatement::CreateTableStatement() : AbstractSQLStatement(CodeElement::DDL_CREATE_TABLE) {

}

CreateTableStatement::~CreateTableStatement() {

}

} /* namespace alinous */
