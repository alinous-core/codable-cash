/*
 * ThisPointerAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/ThisPointerAccess.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"

#include "vm/VirtualMachine.h"
#include "vm/variable_access/FunctionArguments.h"

#include "instance/VmClassInstance.h"

#include "lang/sc_expression/AbstractExpression.h"


namespace alinous {

ThisPointerAccess::ThisPointerAccess()
			: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_THIS_POINTER) {
	this->atype = nullptr;
}

ThisPointerAccess::~ThisPointerAccess() {
	delete this->atype;
}

void ThisPointerAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastInst, CodeElement* element) {
	bool staticMode = false;
	AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);
	if(exp != nullptr){
		staticMode = exp->isStaticMode();
	}

	if(staticMode){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_USE_THIS, actx->getCurrentElement(), L"Can not use this pointer in static method.", {});
		this->hasError = true;
		return;
	}

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
