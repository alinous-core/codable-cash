/*
 * PostIncrementExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_arithmetic/PostIncrementExpression.h"

namespace alinous {

PostIncrementExpression::PostIncrementExpression() : AbstractExpression(CodeElement::EXP_POST_INC) {
	this->exp = nullptr;
	this->ope = 0;
}

PostIncrementExpression::~PostIncrementExpression() {
	delete this->exp;
}

void PostIncrementExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void PostIncrementExpression::setOpe(int ope) noexcept {
	this->ope = ope;
}

} /* namespace alinous */

int alinous::PostIncrementExpression::binarySize() const {
}

void alinous::PostIncrementExpression::toBinary(ByteBuffer* out) {
}

void alinous::PostIncrementExpression::fromBinary(ByteBuffer* in) {
}
