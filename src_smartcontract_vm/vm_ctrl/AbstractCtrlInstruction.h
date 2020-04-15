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
class ObjectReference;

class AbstractCtrlInstruction {
public:
	static const constexpr int RET_NONE{0};
	static const constexpr int RET_BREAK{1};
	static const constexpr int RET_CONTINUE{2};
	static const constexpr int RET_THROW{3};

	AbstractCtrlInstruction();
	virtual ~AbstractCtrlInstruction();

	virtual int control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) = 0;
	virtual ObjectReference* getException() const noexcept;
};

} /* namespace alinous */

#endif /* VM_CTRL_ABSTRACTCTRLINSTRUCTION_H_ */
