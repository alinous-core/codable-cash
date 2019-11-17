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

#include "variable_access/FunctionArguments.h"


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
}

VirtualMachine::~VirtualMachine() {
	if(!this->destried){
		// destroy(); FIXME clear comment
	}

	delete this->sc;

	delete this->stackManager;
	delete this->gc;

	delete this->memory;
	delete this->alloc;

	this->argsRegister = nullptr;
	this->rootReference = nullptr;
}

void VirtualMachine::loadSmartContract(SmartContract* sc) {
	this->sc = sc;
	this->stackManager = new VmStackManager();
}

void VirtualMachine::createScInstance() {
	initialize();
	this->sc->createInstance(this);
}

void VirtualMachine::interpret(const UnicodeString* method) {
	ArrayList<AbstractReference> list;
	interpret(method, &list);
}

void VirtualMachine::interpret(const UnicodeString* method,	ArrayList<AbstractReference>* arguments) {

}

void VirtualMachine::interpret(MethodDeclare* method, VmClassInstance* _this, ArrayList<AbstractReference>* arguments) {
	initialize();

	FunctionArguments args;
	args.setThisPtr(_this);
	setFunctionArguments(&args);

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

	VmStack* stack = new(this) VmStack(this);
	this->stackManager->addStack(stack);

	this->gc->addInstanceReference(root, stack);
}

void VirtualMachine::popStack() {
	VmStack* stack = this->stackManager->top();

	this->stackManager->popStack();

	VmRootReference* root = this->sc->getRootReference();
	this->gc->removeInstanceReference(root, stack);
}

VmStack* VirtualMachine::topStack() const noexcept {
	return this->stackManager->top();
}

void VirtualMachine::clearStack() noexcept {
	while(!this->stackManager->isEmpty()){
		this->stackManager->popStack();
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


void VirtualMachine::destroy() noexcept {
	if(this->sc == nullptr){
		return;
	}

	clearStack();
	this->sc->clearRootReference(this);


	this->gc->garbageCollect();

	this->destried = true;
}

} /* namespace alinous */
