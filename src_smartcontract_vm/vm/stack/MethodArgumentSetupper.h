/*
 * MethodArgumentSetupper.h
 *
 *  Created on: 2020/03/30
 *      Author: iizuka
 */

#ifndef STACK_METHODARGUMENTSETUPPER_H_
#define STACK_METHODARGUMENTSETUPPER_H_

namespace alinous {

class VirtualMachine;
class FunctionArguments;

class MethodArgumentSetupper {
public:
	MethodArgumentSetupper(FunctionArguments* args, VirtualMachine* vm);
	virtual ~MethodArgumentSetupper();

private:
	FunctionArguments* lastArgs;
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* STACK_METHODARGUMENTSETUPPER_H_ */
