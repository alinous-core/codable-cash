/*
 * AnalyzeStackManager.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzeStack.h"

#include "variable_access/StackVariableAccess.h"


namespace alinous {

AnalyzeStackManager::AnalyzeStackManager() {
	this->stack = new ArrayList<AnalyzeStack>();
}

AnalyzeStackManager::~AnalyzeStackManager() {
	this->stack->deleteElements();
	delete this->stack;
}

void AnalyzeStackManager::addFunctionStack() noexcept {
	AnalyzeStack* fstack = new AnalyzeStack(true);
	this->stack->addElement(fstack);
}

void AnalyzeStackManager::popFunctionStack() noexcept {
	int pos = this->stack->size() - 1;
	AnalyzeStack* fstack = this->stack->remove(pos);

	assert(fstack->isFunctionStack());
	delete fstack;
}

void AnalyzeStackManager::addBlockStack() noexcept {
	AnalyzeStack* stack = new AnalyzeStack(true);
	this->stack->addElement(stack);
}

void AnalyzeStackManager::popBlockStack() noexcept {
	int pos = this->stack->size() - 1;
	AnalyzeStack* bstack = this->stack->remove(pos);

	assert(!bstack->isFunctionStack());
	delete bstack;
}

AnalyzeStack* AnalyzeStackManager::top() const noexcept {
	int pos = this->stack->size() - 1;
	return this->stack->get(pos);
}

StackVariableAccess* AnalyzeStackManager::findStackVariableAccess(const UnicodeString* name) const noexcept {
	// find stack access
	StackVariableAccess* access = nullptr;

	int topStack = this->stack->size() - 1;
	for(int i = topStack; i >= 0; --i){
		AnalyzeStack* stack = this->stack->get(i);
		int pos = stack->findStackPosOfVariable(name);

		if(pos >= 0){
			access = new StackVariableAccess(i, pos);
			break;
		}

		if(stack->isFunctionStack()){
			break;
		}
	}

	return access;
}


} /* namespace alinous */
