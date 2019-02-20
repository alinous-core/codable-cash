/*
 * SQLAdditiveExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAdditiveExpression.h"

namespace alinous {

SQLAdditiveExpression::SQLAdditiveExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_ADDITIVE), operations(4) {
}

SQLAdditiveExpression::~SQLAdditiveExpression() {
}

} /* namespace alinous */
