/*
 * ExpressionAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ExpressionAccess.h"

namespace alinous {

ExpressionAccess::ExpressionAccess(AbstractExpression* exp) {
	this->exp = exp;
}

ExpressionAccess::~ExpressionAccess() {
}

void ExpressionAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	// FIXME
}

AnalyzedType* ExpressionAccess::getAnalyzedType() const noexcept {
	return nullptr; // FIXME
}

AbstractVmInstance* ExpressionAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	// FIXME interpret
	return nullptr;
}

} /* namespace alinous */
