/*
 * AnalyzeStackManager.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzeStack.h"



namespace alinous {

AnalyzeStackManager::AnalyzeStackManager() {
	this->stack = new ArrayList<AnalyzeStack>();
}

AnalyzeStackManager::~AnalyzeStackManager() {
	this->stack->deleteElements();
	delete this->stack;
}

void AnalyzeStackManager::addFunctionStack() noexcept {
}

void AnalyzeStackManager::popFunctionStack() noexcept {
}

void AnalyzeStackManager::addBlockStack() noexcept {
}

void AnalyzeStackManager::popBlockStack() noexcept {
}

} /* namespace alinous */
