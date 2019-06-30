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

class UnicodeString;

class VmInstanceStack;
class SmartContract;
class VmMemoryManager;
class VmMalloc;
class GcManager;
class VmStackManager;

class VirtualMachine {
public:
	explicit VirtualMachine(uint64_t memCapacity);
	virtual ~VirtualMachine();

	void loadSmartContract(SmartContract* sc);
	void analyze();
	bool hasError() noexcept;

	void createScInstance();
	void interpret(const UnicodeString* method);

	void newStack();
	void popStack();

	VmMemoryManager* getMemory() noexcept;
	VmMalloc* getAlloc() noexcept;
	GcManager* getGc() noexcept;

private:
	VmInstanceStack* stack;
	SmartContract* sc;

	VmMemoryManager* memory;
	VmStackManager* stackManager;
	VmMalloc* alloc;
	GcManager* gc;
};

} /* namespace alinous */

#endif /* VM_VIRTUALMACHINE_H_ */
