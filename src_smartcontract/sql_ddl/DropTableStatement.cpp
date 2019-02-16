/*
 * DropTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/DropTableStatement.h"

namespace alinous {

DropTableStatement::DropTableStatement() : AbstractSQLStatement(CodeElement::DDL_DROP_TABLE) {
	// TODO Auto-generated constructor stub

}

DropTableStatement::~DropTableStatement() {
	// TODO Auto-generated destructor stub
}

} /* namespace alinous */
