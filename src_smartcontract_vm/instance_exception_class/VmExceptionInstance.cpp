/*
 * VmExceptionInstance.cpp
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#include "instance_exception_class/VmExceptionInstance.h"

namespace alinous {

VmExceptionInstance::VmExceptionInstance(AnalyzedClass* clazz, VirtualMachine* vm)
				: VmClassInstance(clazz, vm) {
	this->element = nullptr;
}

VmExceptionInstance::~VmExceptionInstance() {
	this->element = nullptr;
}

void VmExceptionInstance::setCodeElement(CodeElement* element) noexcept {
	this->element = element;
}

CodeElement* VmExceptionInstance::getElement() const noexcept {
	return this->element;
}


} /* namespace alinous */
