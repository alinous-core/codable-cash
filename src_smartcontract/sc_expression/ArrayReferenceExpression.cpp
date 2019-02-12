/*
 * ArrayReferenceExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/ArrayReferenceExpression.h"

namespace alinous {

ArrayReferenceExpression::ArrayReferenceExpression() : AbstractExpression(CodeElement::EXP_ARRAY_REF) {
	this->exp = nullptr;
}

ArrayReferenceExpression::~ArrayReferenceExpression() {
	delete this->exp;
	this->list.deleteElements();
}

void ArrayReferenceExpression::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void ArrayReferenceExpression::addIndex(AbstractExpression* exp) noexcept {
	this->list.addElement(exp);
}

} /* namespace alinous */
