/*
 * ExpressionAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/ExpressionAccess.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

ExpressionAccess::ExpressionAccess(AbstractExpression* exp)
					: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_EXPRESSION){
	this->exp = exp;
	this->atype = nullptr;
}

ExpressionAccess::~ExpressionAccess() {
	delete this->atype;
}

void ExpressionAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->exp->analyze(actx);
	AnalyzedType at = this->exp->getType(actx);
	this->atype = new AnalyzedType(at);
}

AnalyzedType ExpressionAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* ExpressionAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	AbstractVmInstance* inst = this->exp->interpret(vm);

	return inst;
}

CodeElement* ExpressionAccess::getCodeElement() const noexcept {
	return this->exp;
}

} /* namespace alinous */
