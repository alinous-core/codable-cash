/*
 * ExecControlManager.h
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#ifndef VM_CTRL_EXECCONTROLMANAGER_H_
#define VM_CTRL_EXECCONTROLMANAGER_H_

namespace alinous {

class AbstractCtrlInstruction;
class BlockState;
class CodeElement;

class ExecControlManager {
public:
	ExecControlManager();
	virtual ~ExecControlManager();

	void setInstruction(AbstractCtrlInstruction* instruction) noexcept;
	void consumeInstruction() noexcept;
	void doConsumeInstruction() noexcept;

	int checkStatementCtrl(BlockState* state, CodeElement* lastElement) noexcept;

private:
	AbstractCtrlInstruction* instruction;
	AbstractCtrlInstruction* instruction2Consume;
};

} /* namespace alinous */

#endif /* VM_CTRL_EXECCONTROLMANAGER_H_ */
