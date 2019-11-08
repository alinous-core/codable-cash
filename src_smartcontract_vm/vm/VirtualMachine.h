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
class VmStack;

class MethodDeclare;
class VmClassInstance;
class FunctionArguments;

class VirtualMachine {
public:
	explicit VirtualMachine(uint64_t memCapacity);
	virtual ~VirtualMachine();

	void loadSmartContract(SmartContract* sc);
	void analyze();
	bool hasError() noexcept;

	void createScInstance();
	void interpret(const UnicodeString* method);
	void interpret(MethodDeclare* method, VmClassInstance* _this);

	void newStack();
	void popStack();
	VmStack* topStack() const noexcept;
	void clearStack() noexcept;

	VmMemoryManager* getMemory() noexcept;
	VmMalloc* getAlloc() noexcept;
	GcManager* getGc() noexcept;

	void setFunctionArguments(FunctionArguments* args) noexcept;
	FunctionArguments* getFunctionArguments() const noexcept;

	void initialize();
	void destroy() noexcept;
private:
	SmartContract* sc;

	VmMemoryManager* memory;
	VmStackManager* stackManager;
	VmMalloc* alloc;
	GcManager* gc;

	FunctionArguments* argsRegister;

	bool destried;
	bool initialized;
};

} /* namespace alinous */

#endif /* VM_VIRTUALMACHINE_H_ */
