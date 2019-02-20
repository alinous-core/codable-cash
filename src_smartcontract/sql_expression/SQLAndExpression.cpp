/*
 * SQLAndExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAndExpression.h"

namespace alinous {

SQLAndExpression::SQLAndExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_AND) {
}

SQLAndExpression::~SQLAndExpression() {
}

} /* namespace alinous */
