/*
 * MemberFunctionCallAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/MemberFunctionCallAccess.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang/sc_expression/FunctionCallExpression.h"

#include "instance/VmClassInstance.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance/instance_exception/ExceptionInterrupt.h"


namespace alinous {

MemberFunctionCallAccess::MemberFunctionCallAccess(FunctionCallExpression* exp)
				: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_MEMBER_FUNCTION){
	this->exp = exp;
	this->atype = nullptr;
	this->element = nullptr;
}

MemberFunctionCallAccess::~MemberFunctionCallAccess() {
	delete this->atype;
}

void MemberFunctionCallAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->element = nullptr;

	AnalyzedType at = lastIinst->getAnalyzedType();
	AnalyzedClass* aclass = at.getAnalyzedClass();

	this->exp->analyze(actx, aclass, lastIinst);
	this->atype = new AnalyzedType(this->exp->getType(actx));
}

AnalyzedType MemberFunctionCallAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* MemberFunctionCallAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	if(lastInst == nullptr || lastInst->isNull()){
		NullPointerExceptionClassDeclare::throwException(vm, this->element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	AbstractVmInstance* inst = lastInst;
	VmClassInstance* classInst = dynamic_cast<VmClassInstance*>(inst->getInstance());

	return this->exp->interpret(vm, classInst);
}

CodeElement* MemberFunctionCallAccess::getCodeElement() const noexcept {
	return this->exp;
}

} /* namespace alinous */
