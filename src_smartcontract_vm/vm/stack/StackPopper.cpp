/*
 * StackPopper.cpp
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#include "vm/stack/StackPopper.h"
#include "vm/VirtualMachine.h"

namespace alinous {

StackPopper::StackPopper(VirtualMachine* vm) {
	this->vm = vm;
}

StackPopper::~StackPopper() {
	this->vm->popStack();
}

} /* namespace alinous */
