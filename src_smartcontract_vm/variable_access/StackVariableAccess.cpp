/*
 * StackVariableAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/StackVariableAccess.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzedStackReference.h"
#include "sc_analyze_stack/AnalyzeStack.h"

#include "vm/VirtualMachine.h"

#include "stack/VmStack.h"


namespace alinous {

StackVariableAccess::StackVariableAccess(int stackTopDiff, int pos)
				: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_STACK_VARIABLE){
	this->stackTopDiff = stackTopDiff;
	this->pos = pos;
	this->atype = nullptr;
}

StackVariableAccess::~StackVariableAccess() {
	delete this->atype;
}

void StackVariableAccess::analyze(AnalyzeContext* actx,	AbstractVariableInstraction* lastIinst, CodeElement* element) {
	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	int stackTop = stackMgr->topIndex();

	AnalyzeStack* stack = stackMgr->get(stackTop - this->stackTopDiff);
	AnalyzedStackReference* ref = stack->get(this->pos);

	const AnalyzedType* atype = ref->getType();
	this->atype = new AnalyzedType(*atype);
}

AnalyzedType StackVariableAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* StackVariableAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	int topIndex = vm->topStackIndex();
	VmStack* stack = vm->getStackAt(topIndex - this->stackTopDiff);
	AbstractVmInstance* inst = stack->get(this->pos);

	return inst;
}

CodeElement* StackVariableAccess::getCodeElement() const noexcept {
	return nullptr;
}

} /* namespace alinous */
