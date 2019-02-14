/*
 * PreIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PreIncrementExpression.h"

namespace alinous {

PreIncrementExpression::PreIncrementExpression() : AbstractExpression(CodeElement::EXP_PRE_INC) {
	this->exp = nullptr;
	this->ope = 0;
}

PreIncrementExpression::~PreIncrementExpression() {
	delete this->exp;
}

void PreIncrementExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void PreIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

} /* namespace alinous */
