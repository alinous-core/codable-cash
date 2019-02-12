/*
 * ParenthesisExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/ParenthesisExpression.h"

namespace alinous {

ParenthesisExpression::ParenthesisExpression() : AbstractExpression(CodeElement::EXP_PARENTHESIS) {
	this->exp = nullptr;
}

ParenthesisExpression::~ParenthesisExpression() {
	delete this->exp;
}

void ParenthesisExpression::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
