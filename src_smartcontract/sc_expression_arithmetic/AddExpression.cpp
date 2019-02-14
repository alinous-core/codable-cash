/*
 * AddExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */
#include "sc_expression_arithmetic/AddExpression.h"


namespace alinous {

AddExpression::AddExpression() : AbstractBinaryExpression(CodeElement::EXP_ADD), operations(8) {
}

AddExpression::~AddExpression() {
}

void AddExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

} /* namespace alinous */
