/*
 * ReturnControl.h
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#ifndef VM_CTRL_RETURNCONTROL_H_
#define VM_CTRL_RETURNCONTROL_H_

#include "vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

class ReturnControl : public AbstractCtrlInstruction {
public:
	ReturnControl();
	virtual ~ReturnControl();
};

} /* namespace alinous */

#endif /* VM_CTRL_RETURNCONTROL_H_ */
