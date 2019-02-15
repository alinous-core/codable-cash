/*
 * AllocationExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/AllocationExpression.h"

#include "sc_declare/PackageNameDeclare.h"
#include "sc_expression/FunctionCallExpression.h"

namespace alinous {

AllocationExpression::AllocationExpression() : AbstractExpression(CodeElement::EXP_ALLOCATION) {
	this->packageName = nullptr;
	this->exp = nullptr;
}

AllocationExpression::~AllocationExpression() {
	delete this->packageName;
	delete this->exp;
}

void AllocationExpression::setPackage(PackageNameDeclare* packageName) noexcept {
	this->packageName = packageName;
}

void AllocationExpression::setExpression(FunctionCallExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
