/*
 * RelationalExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_logical/RelationalExpression.h"

namespace alinous {

RelationalExpression::RelationalExpression() : AbstractExpression(CodeElement::EXP_CND_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

RelationalExpression::~RelationalExpression() {
	delete this->left;
	delete this->right;
}

void RelationalExpression::setLeft(AbstractExpression* exp) noexcept {
	this->left = exp;
}

void RelationalExpression::setRight(AbstractExpression* exp) noexcept {
	this->right = exp;
}

void RelationalExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

} /* namespace alinous */

int alinous::RelationalExpression::binarySize() const {
}

void alinous::RelationalExpression::toBinary(ByteBuffer* out) {
}

void alinous::RelationalExpression::fromBinary(ByteBuffer* in) {
}
