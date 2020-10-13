/*
 * ExceptionControl.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef VM_CTRL_EXCEPTIONCONTROL_H_
#define VM_CTRL_EXCEPTIONCONTROL_H_

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

class VmExceptionInstance;
class AbstractReference;
class ObjectReference;
class VirtualMachine;

class ExceptionControl : public AbstractCtrlInstruction {
public:
	ExceptionControl(AbstractReference* exception);
	virtual ~ExceptionControl();

	virtual int control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement);
	virtual ObjectReference* getException() const noexcept;

	void releaseException(VirtualMachine* vm);
private:
	ObjectReference* exception;
};

} /* namespace alinous */

#endif /* VM_CTRL_EXCEPTIONCONTROL_H_ */
