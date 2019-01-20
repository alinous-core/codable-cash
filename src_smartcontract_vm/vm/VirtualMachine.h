/*
 * VirtualMachine.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef VM_VIRTUALMACHINE_H_
#define VM_VIRTUALMACHINE_H_

namespace alinous {

class VmInstanceStack;
class SmartContract;

class VirtualMachine {
public:
	VirtualMachine();
	virtual ~VirtualMachine();

	void loadSmartContract(SmartContract* sc);

private:
	VmInstanceStack* stack;
	SmartContract* sc;
};

} /* namespace alinous */

#endif /* VM_VIRTUALMACHINE_H_ */
