/*
 * FunctionCallExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/FunctionCallExpression.h"
#include "base/UnicodeString.h"

namespace alinous {

FunctionCallExpression::FunctionCallExpression() : AbstractExpression(CodeElement::EXP_FUNCTIONCALL) {
	this->name = nullptr;
}

FunctionCallExpression::~FunctionCallExpression() {
	delete this->name;
	this->args.deleteElements();
}

void FunctionCallExpression::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

void FunctionCallExpression::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}

} /* namespace alinous */
