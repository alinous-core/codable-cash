/*
 * AbstractCtrlInstruction.h
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#ifndef VM_CTRL_ABSTRACTCTRLINSTRUCTION_H_
#define VM_CTRL_ABSTRACTCTRLINSTRUCTION_H_

namespace alinous {

class ExecControlManager;
class BlockState;
class CodeElement;

class AbstractCtrlInstruction {
public:
	AbstractCtrlInstruction();
	virtual ~AbstractCtrlInstruction();

	virtual bool control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) = 0;
};

} /* namespace alinous */

#endif /* VM_CTRL_ABSTRACTCTRLINSTRUCTION_H_ */
