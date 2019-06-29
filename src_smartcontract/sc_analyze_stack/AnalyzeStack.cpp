/*
 * AnalyzeStack.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "sc_analyze_stack/AnalyzeStack.h"
#include "sc_analyze_stack/AnalyzedStackReference.h"

#include "base/UnicodeString.h"

namespace alinous {

AnalyzeStack::AnalyzeStack(bool functionStack) {
	this->functionStack = functionStack;
}

AnalyzeStack::~AnalyzeStack() {
	this->variables.deleteElements();
}

void AnalyzeStack::addVariableDeclare(AnalyzedStackReference* ref) noexcept {
	this->variables.addElement(ref);
	this->map.put(ref->getName(), ref);
}

bool AnalyzeStack::isFunctionStack() const noexcept {
	return this->functionStack;
}

} /* namespace alinous */
