/*
 * LiteralExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/LiteralExpression.h"
#include "base/UnicodeString.h"

namespace alinous {

LiteralExpression::LiteralExpression() : AbstractExpression(CodeElement::EXP_LITERAL){
	this->str = nullptr;
	this->dquote = true;
}

LiteralExpression::~LiteralExpression() {
	delete this->str;
}

void LiteralExpression::setString(UnicodeString* str, bool dquote) noexcept {
	this->str = str;
	this->dquote = dquote;
}

} /* namespace alinous */

int alinous::LiteralExpression::binarySize() const {
}

void alinous::LiteralExpression::toBinary(ByteBuffer* out) {
}

void alinous::LiteralExpression::fromBinary(ByteBuffer* in) {
}
