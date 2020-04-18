/*
 * ExceptionInterrupt.cpp
 *
 *  Created on: 2020/04/18
 *      Author: iizuka
 */

#include "instance_exception/ExceptionInterrupt.h"

#include "vm/VirtualMachine.h"

#include "vm_ctrl/ExecControlManager.h"

namespace alinous {

ExceptionInterrupt::ExceptionInterrupt() {

}

ExceptionInterrupt::~ExceptionInterrupt() {

}

void ExceptionInterrupt::interruptPoint(VirtualMachine* vm) {
	ExecControlManager* ctrl = vm->getCtrl();
	if(ctrl->isExceptionThrown()){
		throw new ExceptionInterrupt();
	}
}

} /* namespace alinous */
