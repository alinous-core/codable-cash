/*
 * VirtualMachine.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef VM_VIRTUALMACHINE_H_
#define VM_VIRTUALMACHINE_H_
#include <cstdint>

namespace alinous {

class VmInstanceStack;
class SmartContract;
class VmMemoryManager;

class VirtualMachine {
public:
	explicit VirtualMachine(uint64_t memCapacity);
	virtual ~VirtualMachine();

	void loadSmartContract(SmartContract* sc);
	void analyze();

	VmMemoryManager* getMemory() noexcept;

private:
	VmInstanceStack* stack;
	SmartContract* sc;

	VmMemoryManager* memory;
};

} /* namespace alinous */

#endif /* VM_VIRTUALMACHINE_H_ */
