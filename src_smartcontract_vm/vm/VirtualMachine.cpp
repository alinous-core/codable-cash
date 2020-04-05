/*
 * VirtualMachine.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"

#include "memory/VmMemoryManager.h"
#include "instance_parts/VmMalloc.h"
#include "instance_gc/GcManager.h"
#include "instance/VmClassInstance.h"

#include "instance_ref/AbstractReference.h"

#include "stack/VmStackManager.h"
#include "stack/VmStack.h"

#include "instance_ref/VmRootReference.h"

#include "sc_declare/MethodDeclare.h"
#include "sc_statement/StatementBlock.h"

#include "sc_analyze_functions/FunctionScoreCalc.h"
#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableMethodEntry.h"
#include "sc_analyze_functions/MethodScore.h"

#include "variable_access/FunctionArguments.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "instance_exception/AbstructProgramException.h"

#include "ext_arguments/AbstractFunctionExtArguments.h"

#include "vm/exceptions.h"

#include "stack/StackPopper.h"

#include "vm_ctrl/ExecControlManager.h"

namespace alinous {

VirtualMachine::VirtualMachine(uint64_t memCapacity) {
	this->sc = nullptr;
	this->memory = new VmMemoryManager(memCapacity);
	this->alloc = new VmMalloc(this);
	this->gc = new GcManager();
	this->stackManager = nullptr;
	this->argsRegister = nullptr;
	this->destried = false;
	this->initialized = false;
	this->rootReference = nullptr;
	this->ctrl = new ExecControlManager();
}

VirtualMachine::~VirtualMachine() {
	if(!this->destried){
		destroy();
	}

	delete this->sc;

	delete this->stackManager;
	delete this->gc;

	delete this->memory;
	delete this->alloc;
	delete this->ctrl;

	this->argsRegister = nullptr;
	this->rootReference = nullptr;

	this->exceptions.deleteElements();
}

void VirtualMachine::loadSmartContract(SmartContract* sc) {
	this->sc = sc;
	this->stackManager = new VmStackManager();
}

VmClassInstance* VirtualMachine::createScInstance() {
	initialize();
	try{
		return this->sc->createInstance(this);
	}
	catch(AbstructProgramException* e){
		this->exceptions.addElement(e);
	}

	return nullptr;
}

void VirtualMachine::interpret(const UnicodeString* method) {
	ArrayList<AbstractFunctionExtArguments> list;
	interpret(method, &list);
}

void VirtualMachine::interpret(const UnicodeString* method,	ArrayList<AbstractFunctionExtArguments>* arguments) {
	VmClassInstance* _this = dynamic_cast<VmClassInstance*>(this->sc->getRootReference()->getInstance());
	AnalyzedClass* aclass = _this->getAnalyzedClass();

	const UnicodeString* fqn = aclass->getFullQualifiedName();

	AnalyzeContext* actx = this->sc->getAnalyzeContext();
	VTableRegistory* vreg = actx->getVtableRegistory();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, aclass);

	FunctionScoreCalc calc(classEntry);

	// arguments type
	ArrayList<AnalyzedType> typeList;
	typeList.setDeleteOnExit();

	int maxLoop = arguments->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractFunctionExtArguments* extArg = arguments->get(i);

		AnalyzedType at = extArg->getType();
		typeList.addElement(new AnalyzedType(at));
	}

	MethodScore* score = calc.findMethod(method, &typeList);
	if(score == nullptr){
		throw new VmMethodNotFoundException(__FILE__, __LINE__);
	}

	VTableMethodEntry* methodEntry = score->getEntry();
	MethodDeclare* methodDeclare = methodEntry->getMethod();

	FunctionArguments args;
	args.setThisPtr(_this);

	for(int i = 0; i != maxLoop; ++i){
		AbstractFunctionExtArguments* extArg = arguments->get(i);

		AbstractVmInstance* inst = extArg->interpret(this);

		args.addSubstance(inst != nullptr ? inst->getInstance() : nullptr);
	}


	// top stack
	this->newStack();
	StackPopper popStack(this);
	VmStack* stack = this->topStack();

	methodDeclare->interpret(&args, this);
}

void VirtualMachine::interpret(MethodDeclare* method, VmClassInstance* _this, ArrayList<AbstractFunctionExtArguments>* arguments) {
	initialize();

	FunctionArguments args;
	args.setThisPtr(_this);

	method->interpret(&args, this);
}

VmMemoryManager* VirtualMachine::getMemory() noexcept {
	return this->memory;
}

VmMalloc* VirtualMachine::getAlloc() noexcept {
	return this->alloc;
}

void VirtualMachine::analyze() {
	this->sc->analyze(this);
}

bool VirtualMachine::hasError() noexcept {
	return this->sc->hasError();
}

void VirtualMachine::newStack() {
	VmRootReference* root = this->sc->getRootReference();

	VmStack* stack = new(this) VmStack(root, this);
	this->stackManager->addStack(stack);

	this->gc->registerObject(stack);
}

void VirtualMachine::popStack() {
	VmStack* stack = this->stackManager->top();

	this->stackManager->popStack();

	this->gc->removeObject(stack);
}

VmStack* VirtualMachine::topStack() const noexcept {
	return this->stackManager->top();
}

int VirtualMachine::topStackIndex() const noexcept {
	return this->stackManager->size() - 1;
}

VmStack* VirtualMachine::getStackAt(int pos) const noexcept {
	return this->stackManager->get(pos);
}

void VirtualMachine::clearStack() noexcept {
	VmRootReference* root = this->sc->getRootReference();

	while(!this->stackManager->isEmpty()){
		VmStack* stack = this->stackManager->top();
		this->stackManager->popStack();

		this->gc->removeObject(stack);
	}
}

GcManager* VirtualMachine::getGc() noexcept {
	return this->gc;
}

FunctionArguments* VirtualMachine::getFunctionArguments() const noexcept {
	return this->argsRegister;
}

void VirtualMachine::setFunctionArguments(FunctionArguments* args) noexcept {
	this->argsRegister = args;
}

void VirtualMachine::initialize() {
	if(this->initialized){
		return;
	}

	this->sc->initialize(this);
	this->initialized = true;
}

void VirtualMachine::setVmRootReference(VmRootReference* rootReference) noexcept {
	this->rootReference = rootReference;
}

VmRootReference* VirtualMachine::getVmRootReference() const noexcept {
	return this->rootReference;
}

SmartContract* VirtualMachine::getSmartContract() const noexcept {
	return this->sc;
}

void VirtualMachine::destroy() noexcept {
	if(this->sc == nullptr || this->sc->getRootReference() == nullptr){
		return;
	}

	clearStack();
	this->sc->getRootReference()->clearInnerReferences();
	this->gc->garbageCollect();

	this->sc->clearRootReference(this);

	this->destried = true;
}

ExecControlManager* VirtualMachine::getCtrl() const noexcept {
	return this->ctrl;
}

ArrayList<AbstructProgramException>& VirtualMachine::getExceptions() noexcept {
	return this->exceptions;
}


} /* namespace alinous */
