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

StackVariableAccess::StackVariableAccess(int stackPos, int pos) {
	this->stackPos = stackPos;
	this->pos = pos;
	this->type = nullptr;
}

StackVariableAccess::~StackVariableAccess() {
	delete this->type;
}

void StackVariableAccess::analyze(AnalyzeContext* actx,	AbstractVariableInstraction* lastIinst, CodeElement* element) {
	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	AnalyzeStack* stack = stackMgr->get(this->stackPos);
	AnalyzedStackReference* ref = stack->get(this->pos);

	const AnalyzedType* atype = ref->getType();
	this->type = new AnalyzedType(*atype);
}

AnalyzedType StackVariableAccess::getAnalyzedType() const noexcept {
	return *this->type;
}

AbstractVmInstance* StackVariableAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	VmStack* stack = vm->getStackAt(this->stackPos);
	AbstractVmInstance* inst = stack->get(this->pos);

	return inst;
}

CodeElement* StackVariableAccess::getCodeElement() const noexcept {
	return nullptr;
}

} /* namespace alinous */
