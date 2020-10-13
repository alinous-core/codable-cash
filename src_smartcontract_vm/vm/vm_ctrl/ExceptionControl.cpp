/*
 * ExceptionControl.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "vm/vm_ctrl/ExceptionControl.h"

#include "instance/instance_exception_class/VmExceptionInstance.h"

#include "instance/instance_ref/ObjectReference.h"

#include "instance/instance_gc/GcManager.h"


namespace alinous {

ExceptionControl::ExceptionControl(AbstractReference* exception) {
	this->exception = dynamic_cast<ObjectReference*>(exception);
}

ExceptionControl::~ExceptionControl() {

}

int ExceptionControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {

	return AbstractCtrlInstruction::RET_THROW;
}

ObjectReference* ExceptionControl::getException() const noexcept {
	return this->exception;
}

void ExceptionControl::releaseException(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	gc->removeObject(this->exception);
	this->exception = nullptr;
}

} /* namespace alinous */
