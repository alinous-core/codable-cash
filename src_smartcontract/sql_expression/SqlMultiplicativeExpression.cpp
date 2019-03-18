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

int alinous::SqlMultiplicativeExpression::binarySize() const {
}

void alinous::SqlMultiplicativeExpression::toBinary(ByteBuffer* out) {
}

void alinous::SqlMultiplicativeExpression::fromBinary(ByteBuffer* in) {
}
