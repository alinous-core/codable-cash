/*
 * SqlMultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SqlMultiplicativeExpression.h"

namespace alinous {

SqlMultiplicativeExpression::SqlMultiplicativeExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_MULTIPLICATIVE), operations(4) {
}

SqlMultiplicativeExpression::~SqlMultiplicativeExpression() {
}

void SqlMultiplicativeExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

} /* namespace alinous */
