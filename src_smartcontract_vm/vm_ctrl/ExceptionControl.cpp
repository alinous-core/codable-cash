/*
 * ExceptionControl.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "vm_ctrl/ExceptionControl.h"

#include "instance_exception_class/VmExceptionInstance.h"

namespace alinous {

ExceptionControl::ExceptionControl(VmExceptionInstance* exception) {
	this->exception = exception;
}

ExceptionControl::~ExceptionControl() {
	delete this->exception;
}

int ExceptionControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {

	return AbstractCtrlInstruction::RET_THROW;
}

} /* namespace alinous */
