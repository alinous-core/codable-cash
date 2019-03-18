/*
 * ShiftExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/ShiftExpression.h"

namespace alinous {

ShiftExpression::ShiftExpression() : AbstractBinaryExpression(CodeElement::EXP_SHIFT), operations(4) {
}

ShiftExpression::~ShiftExpression() {
}

void ShiftExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int ShiftExpression::binarySize() const {
}

void ShiftExpression::toBinary(ByteBuffer* out) {
}

void ShiftExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
