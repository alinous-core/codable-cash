/*
 * ExceptionControl.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "vm_ctrl/ExceptionControl.h"

#include "instance_exception_class/VmExceptionInstance.h"

#include "instance_ref/ObjectReference.h"

namespace alinous {

ExceptionControl::ExceptionControl(AbstractReference* exception) {
	this->exception = dynamic_cast<ObjectReference*>(exception);
}

ExceptionControl::~ExceptionControl() {

}

int ExceptionControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {

	return AbstractCtrlInstruction::RET_THROW;
}

} /* namespace alinous */
