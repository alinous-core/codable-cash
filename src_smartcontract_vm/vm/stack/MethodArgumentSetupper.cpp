/*
 * MethodArgumentSetupper.cpp
 *
 *  Created on: 2020/03/30
 *      Author: iizuka
 */

#include "vm/stack/MethodArgumentSetupper.h"

#include "vm/VirtualMachine.h"


namespace alinous {

MethodArgumentSetupper::MethodArgumentSetupper(FunctionArguments* args, VirtualMachine* vm) {
	this->lastArgs = vm->getFunctionArguments();
	this->vm = vm;

	vm->setFunctionArguments(args);
}

MethodArgumentSetupper::~MethodArgumentSetupper() {
	vm->setFunctionArguments(this->lastArgs);
}

} /* namespace alinous */
