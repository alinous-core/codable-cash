/*
 * BooleanLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/BooleanLiteral.h"

namespace alinous {

BooleanLiteral::BooleanLiteral() : AbstractExpression(CodeElement::EXP_BOOLEAN_LITERAL) {
	this->value = false;
}

BooleanLiteral::~BooleanLiteral() {
}

void BooleanLiteral::setValue(bool v) noexcept {
	this->value = v;
}

} /* namespace alinous */

int alinous::BooleanLiteral::binarySize() const {
}

void alinous::BooleanLiteral::toBinary(ByteBuffer* out) {
}

void alinous::BooleanLiteral::fromBinary(ByteBuffer* in) {
}
