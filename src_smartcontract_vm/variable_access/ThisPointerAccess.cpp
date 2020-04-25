/*
 * ThisPointerAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ThisPointerAccess.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"
#include "variable_access/FunctionArguments.h"

#include "instance/VmClassInstance.h"

namespace alinous {

ThisPointerAccess::ThisPointerAccess()
			: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_THIS_POINTER) {
	this->atype = nullptr;
}

ThisPointerAccess::~ThisPointerAccess() {
	delete this->atype;
}

void ThisPointerAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastInst, CodeElement* element) {
	AnalyzedClass* clazz = actx->getThisClass();

	this->atype = new AnalyzedType(clazz);
}

AnalyzedType ThisPointerAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* ThisPointerAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	FunctionArguments* args = vm->getFunctionArguments();
	VmClassInstance* inst = args->getThisPtr();

	return inst;
}

CodeElement* alinous::ThisPointerAccess::getCodeElement() const noexcept {
	return nullptr;
}

} /* namespace alinous */
