/*
 * AbstractSQLStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql/AbstractSQLStatement.h"

namespace alinous {

AbstractSQLStatement::AbstractSQLStatement(int kind) : AbstractStatement(kind) {
}

AbstractSQLStatement::~AbstractSQLStatement() {
}

} /* namespace alinous */
