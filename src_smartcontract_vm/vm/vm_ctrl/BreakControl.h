/*
 * BreakControl.h
 *
 *  Created on: 2020/04/08
 *      Author: iizuka
 */

#ifndef VM_CTRL_BREAKCONTROL_H_
#define VM_CTRL_BREAKCONTROL_H_

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

class BreakControl: public AbstractCtrlInstruction {
public:
	BreakControl();
	virtual ~BreakControl();

	virtual int control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement);
};

} /* namespace alinous */

#endif /* VM_CTRL_BREAKCONTROL_H_ */
