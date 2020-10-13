/*
 * AnalyzeStackPopper.cpp
 *
 *  Created on: 2019/06/29
 *      Author: iizuka
 */

#include "engine/sc_analyze_stack/AnalyzeStackPopper.h"
#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

namespace alinous {

AnalyzeStackPopper::AnalyzeStackPopper(AnalyzeStackManager* stack, bool func) {
	this->stack = stack;
	this->func = func;
}

AnalyzeStackPopper::~AnalyzeStackPopper() {
	if(this->func){
		this->stack->popFunctionStack();
	}else{
		this->stack->popBlockStack();
	}
}

} /* namespace alinous */
