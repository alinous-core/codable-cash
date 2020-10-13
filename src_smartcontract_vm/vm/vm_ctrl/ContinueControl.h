/*
 * ContinueControl.h
 *
 *  Created on: 2020/04/08
 *      Author: iizuka
 */

#ifndef VM_CTRL_CONTINUECONTROL_H_
#define VM_CTRL_CONTINUECONTROL_H_

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

class ContinueControl: public AbstractCtrlInstruction {
public:
	ContinueControl();
	virtual ~ContinueControl();

	virtual int control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement);
};

} /* namespace alinous */

#endif /* VM_CTRL_CONTINUECONTROL_H_ */
