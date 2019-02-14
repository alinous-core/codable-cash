/*
 * CastExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/CastExpression.h"
#include "sc_declare_types/AbstractType.h"

namespace alinous {

CastExpression::CastExpression() : AbstractExpression(CodeElement::EXP_CAST) {
	this->exp = nullptr;
	this->type = nullptr;
}

CastExpression::~CastExpression() {
	delete this->exp;
	delete this->type;
}

void CastExpression::setType(AbstractType* type) noexcept {
	this->type = type;
}

void CastExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
