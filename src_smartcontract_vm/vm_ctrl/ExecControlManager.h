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

class ExecControlManager {
public:
	ExecControlManager();
	virtual ~ExecControlManager();

	void setInstruction(AbstractCtrlInstruction* instruction) noexcept;

private:
	AbstractCtrlInstruction* instruction;
};

} /* namespace alinous */

#endif /* VM_CTRL_EXECCONTROLMANAGER_H_ */
