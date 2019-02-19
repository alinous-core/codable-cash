/*
 * AbstractSQLBinaryExpression.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

AbstractSQLBinaryExpression::AbstractSQLBinaryExpression(int kind) : AbstractSQLExpression(kind) {
}

AbstractSQLBinaryExpression::~AbstractSQLBinaryExpression() {
}

} /* namespace alinous */
