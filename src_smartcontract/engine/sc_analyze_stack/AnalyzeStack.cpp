/*
 * AnalyzeStack.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "engine/sc_analyze_stack/AnalyzeStack.h"
#include "engine/sc_analyze_stack/AnalyzedStackReference.h"

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

int AnalyzeStack::findStackPosOfVariable(const UnicodeString* name) const noexcept {
	AnalyzedStackReference* ref = this->map.get(name);
	if(ref == nullptr){
		return -1;
	}

	int maxLoop = this->variables.size();
	int pos = -1;

	// find stack pos
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedStackReference* refStack = this->variables.get(i);
		if(ref == refStack){
			pos = i;
			break;
		}
	}

	return pos;
}

AnalyzedStackReference* AnalyzeStack::get(int pos) const noexcept {
	return this->variables.get(pos);
}

} /* namespace alinous */
