/*
 * EqualityExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/EqualityExpression.h"

namespace alinous {

EqualityExpression::EqualityExpression() : AbstractExpression(CodeElement::EXP_CND_EQ) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

EqualityExpression::~EqualityExpression() {
	delete this->left;
	delete this->right;
}

void EqualityExpression::setLeft(AbstractExpression* exp) noexcept {
	this->left = exp;
}

void EqualityExpression::setRight(AbstractExpression* exp) noexcept {
	this->right = exp;
}

void EqualityExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

} /* namespace alinous */
