/*
 * AnalyzeContext.cpp
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */

#include "sc/AnalyzeContext.h"

namespace alinous {

AnalyzeContext::AnalyzeContext() {
	this->vm = nullptr;
}

AnalyzeContext::~AnalyzeContext() {
	this->vm = nullptr; // safe
}

void AnalyzeContext::setVm(VirtualMachine* vm) noexcept {
	this->vm = vm;
}

} /* namespace alinous */
