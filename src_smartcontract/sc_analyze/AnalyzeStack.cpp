/*
 * AnalyzeStack.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "sc_analyze/AnalyzeStack.h"

namespace alinous {

AnalyzeStack::AnalyzeStack(bool functionStack) {
	this->functionStack = functionStack;
}

AnalyzeStack::~AnalyzeStack() {
	this->variables.deleteElements();
}

} /* namespace alinous */
