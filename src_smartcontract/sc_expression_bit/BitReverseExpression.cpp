/*
 * BitReverseExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_bit/BitReverseExpression.h"

namespace alinous {

BitReverseExpression::BitReverseExpression() : AbstractExpression(CodeElement::EXP_BIT_REV) {
	this->exp = nullptr;
}

BitReverseExpression::~BitReverseExpression() {
	delete this->exp;
}

void BitReverseExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
