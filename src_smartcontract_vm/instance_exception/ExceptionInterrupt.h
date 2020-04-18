/*
 * ExceptionInterrupt.h
 *
 *  Created on: 2020/04/18
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_EXCEPTIONINTERRUPT_H_
#define INSTANCE_EXCEPTION_EXCEPTIONINTERRUPT_H_


namespace alinous {

class VirtualMachine;

class ExceptionInterrupt {
public:
	ExceptionInterrupt();
	virtual ~ExceptionInterrupt();


	static void interruptPoint(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_EXCEPTIONINTERRUPT_H_ */
