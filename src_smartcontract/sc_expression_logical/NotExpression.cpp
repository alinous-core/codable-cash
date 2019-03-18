/*
 * NotExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/NotExpression.h"

namespace alinous {

NotExpression::NotExpression() : AbstractExpression(CodeElement::EXP_CND_NOT) {
	this->exp = nullptr;
}

NotExpression::~NotExpression() {
	delete this->exp;
}

void NotExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */

int alinous::NotExpression::binarySize() const {
}

void alinous::NotExpression::toBinary(ByteBuffer* out) {
}

void alinous::NotExpression::fromBinary(ByteBuffer* in) {
}
