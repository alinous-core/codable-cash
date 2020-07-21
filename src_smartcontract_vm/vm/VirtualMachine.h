/*
 * VirtualMachine.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef VM_VIRTUALMACHINE_H_
#define VM_VIRTUALMACHINE_H_
#include <cstdint>

#include "base/ArrayList.h"

namespace codablecash {
class CodableDatabase;
class SelectScanPlanner;
}
using namespace codablecash;

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
class VmRootReference;
class AbstractReference;

class VmExceptionInstance;
class AbstractFunctionExtArguments;
class ExecControlManager;

class Exception;
class CodeElement;
class AnalyzedClass;
class ObjectReference;
class ExtExceptionObject;
class ReservedClassRegistory;

class VmTransactionHandler;
class File;

class VirtualMachine {
public:
	explicit VirtualMachine(uint64_t memCapacity);
	virtual ~VirtualMachine();

	void loadSmartContract(SmartContract* sc);
	void analyze();
	bool hasError() noexcept;
	bool hasAnalyzeError(int code) noexcept;

	VmClassInstance* createScInstance();

	void interpret(const UnicodeString* method, ArrayList<AbstractFunctionExtArguments>* arguments);
	void interpret(const UnicodeString* method);
	void interpret(MethodDeclare* method, VmClassInstance* _this, ArrayList<AbstractFunctionExtArguments>* arguments);

	void newStack();
	void popStack();
	VmStack* topStack() const noexcept;
	int topStackIndex() const noexcept;
	VmStack* getStackAt(int pos) const noexcept;
	void clearStack() noexcept;

	VmMemoryManager* getMemory() noexcept;
	VmMalloc* getAlloc() noexcept;
	GcManager* getGc() noexcept;

	ExecControlManager* getCtrl() const noexcept;
	void throwException(VmExceptionInstance* exception, const CodeElement* element) noexcept;
	ObjectReference* catchException(AnalyzedClass* exClass) noexcept;
	void releaseMainInstance() noexcept;

	void setFunctionArguments(FunctionArguments* args) noexcept;
	FunctionArguments* getFunctionArguments() const noexcept;

	void setVmRootReference(VmRootReference* rootReference) noexcept;
	VmRootReference* getVmRootReference() const noexcept;

	SmartContract* getSmartContract() const noexcept;

	void initialize();
	void destroy() noexcept;

	ArrayList<Exception>& getExceptions() noexcept;
	ExtExceptionObject* getUncaughtException() noexcept;

	ReservedClassRegistory* getReservedClassRegistory() const noexcept;

	// catch statement
	void setCaught(bool caught) noexcept;
	bool isCaught() const noexcept;



	// database and transaction
	VmTransactionHandler* getTransactionHandler() const noexcept;
	void loadDatabase(const File* dbdir);

	const CodeElement* getLastElement() const noexcept {
		return lastElement;
	}
	void setLastElement(const CodeElement* lastElement) {
		this->lastElement = lastElement;
	}

	void setSelectPlanner(SelectScanPlanner* planner) noexcept;
	void popSelectPlanner() noexcept;
	SelectScanPlanner* getSelectPlanner() const noexcept;
	bool isSelectPlanning() const noexcept;
private:
	void checkUncaughtException();

private:
	SmartContract* sc;

	VmMemoryManager* memory;
	VmStackManager* stackManager;
	VmMalloc* alloc;
	GcManager* gc;
	ExecControlManager* ctrl;

	FunctionArguments* argsRegister;
	VmRootReference* rootReference;

	bool destried;
	bool initialized;

	ArrayList<Exception> exceptions;
	ObjectReference* uncaughtException;

	const CodeElement* lastElement;

	// catch test
	bool caught;

	// database engine
	CodableDatabase* db;
	VmTransactionHandler* trxHandler;

	ArrayList<SelectScanPlanner> selectPlannerList;
};

} /* namespace alinous */

#endif /* VM_VIRTUALMACHINE_H_ */
