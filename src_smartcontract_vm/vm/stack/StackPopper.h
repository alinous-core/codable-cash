/*
 * StackPopper.h
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#ifndef STACK_STACKPOPPER_H_
#define STACK_STACKPOPPER_H_

namespace alinous {
class VirtualMachine;
}

namespace alinous {

class StackPopper {
public:
	StackPopper(VirtualMachine* vm);
	virtual ~StackPopper();

private:
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* STACK_STACKPOPPER_H_ */
