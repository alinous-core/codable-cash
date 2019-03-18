/*
 * MultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/MultiplicativeExpression.h"


namespace alinous {

MultiplicativeExpression::MultiplicativeExpression() : AbstractBinaryExpression(CodeElement::EXP_MUL), operations(8) {
}

MultiplicativeExpression::~MultiplicativeExpression() {
}

void MultiplicativeExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

} /* namespace alinous */

int alinous::MultiplicativeExpression::binarySize() const {
}

void alinous::MultiplicativeExpression::toBinary(ByteBuffer* out) {
}

void alinous::MultiplicativeExpression::fromBinary(ByteBuffer* in) {
}
