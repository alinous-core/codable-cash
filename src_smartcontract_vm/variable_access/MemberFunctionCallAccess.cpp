/*
 * MemberFunctionCallAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/MemberFunctionCallAccess.h"

#include "sc_analyze/AnalyzedType.h"

#include "sc_expression/FunctionCallExpression.h"

#include "instance/VmClassInstance.h"


namespace alinous {

MemberFunctionCallAccess::MemberFunctionCallAccess(FunctionCallExpression* exp) {
	this->exp = exp;
	this->atype = nullptr;
}

MemberFunctionCallAccess::~MemberFunctionCallAccess() {
	delete this->atype;
}

void MemberFunctionCallAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	AnalyzedType at = lastIinst->getAnalyzedType();
	AnalyzedClass* aclass = at.getAnalyzedClass();

	this->exp->analyze(actx, aclass);
	this->atype = new AnalyzedType(this->exp->getType(actx));
}

AnalyzedType MemberFunctionCallAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* MemberFunctionCallAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	AbstractVmInstance* inst = lastInst;
	VmClassInstance* classInst = dynamic_cast<VmClassInstance*>(inst);

	return this->exp->interpret(vm, classInst);
}


} /* namespace alinous */
