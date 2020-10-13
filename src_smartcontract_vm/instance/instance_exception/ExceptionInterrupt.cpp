/*
 * ExceptionInterrupt.cpp
 *
 *  Created on: 2020/04/18
 *      Author: iizuka
 */

#include "instance/instance_exception/ExceptionInterrupt.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_ctrl/ExecControlManager.h"

#include "instance/VmClassInstance.h"

#include "instance/instance_gc/GcManager.h"


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

void ExceptionInterrupt::interruptPoint(VirtualMachine* vm,	VmClassInstance* inst) {
	ExecControlManager* ctrl = vm->getCtrl();
	if(ctrl->isExceptionThrown()){
		GcManager* gc = vm->getGc();
		gc->handleFloatingObject(inst);

		throw new ExceptionInterrupt();
	}
}

} /* namespace alinous */
