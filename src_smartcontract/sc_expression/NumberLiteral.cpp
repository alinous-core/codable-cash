/*
 * NumberLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NumberLiteral.h"
#include "base/UnicodeString.h"

namespace alinous {

NumberLiteral::NumberLiteral() : AbstractExpression(CodeElement::EXP_NUMBER_LITERAL) {
	this->str = nullptr;
}

NumberLiteral::~NumberLiteral() {
	delete this->str;
}

void NumberLiteral::setValue(UnicodeString* str) noexcept {
	this->str = str;
}

} /* namespace alinous */
