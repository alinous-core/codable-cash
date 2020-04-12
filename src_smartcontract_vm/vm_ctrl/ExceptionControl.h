/*
 * ExceptionControl.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef VM_CTRL_EXCEPTIONCONTROL_H_
#define VM_CTRL_EXCEPTIONCONTROL_H_

#include "vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

class AbstractProgramException;

class ExceptionControl : public AbstractCtrlInstruction {
public:
	ExceptionControl(AbstractProgramException* exception);
	virtual ~ExceptionControl();

	virtual int control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement);

private:
	AbstractProgramException* exception;
};

} /* namespace alinous */

#endif /* VM_CTRL_EXCEPTIONCONTROL_H_ */
