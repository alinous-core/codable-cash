/*
 * NegateExpression.cpp
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/NegateExpression.h"

namespace alinous {

NegateExpression::NegateExpression() : AbstractExpression(CodeElement::EXP_NEGATE) {
	this->exp = nullptr;
}

NegateExpression::~NegateExpression() {
	delete this->exp;
}

void NegateExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
