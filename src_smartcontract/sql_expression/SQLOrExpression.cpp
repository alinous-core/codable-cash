/*
 * SQLOrExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLOrExpression.h"

namespace alinous {

SQLOrExpression::SQLOrExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_OR) {
}

SQLOrExpression::~SQLOrExpression() {
}

} /* namespace alinous */
