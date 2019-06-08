/*
 * VirtualMachine.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "vm/VirtualMachine.h"
#include "instance/VmInstanceStack.h"
#include "sc/SmartContract.h"

#include "memory/VmMemoryManager.h"
#include "instance_parts/VmMalloc.h"
#include "instance_gc/GcManager.h"

namespace alinous {

VirtualMachine::VirtualMachine(uint64_t memCapacity) {
	this->stack = nullptr;
	this->sc = nullptr;
	this->memory = new VmMemoryManager(memCapacity);
	this->alloc = new VmMalloc(this);
	this->gc = new GcManager();
}

VirtualMachine::~VirtualMachine() {
	delete this->sc;
	delete this->stack;
	delete this->memory;
	delete this->alloc;
	delete this->gc;
}

void VirtualMachine::loadSmartContract(SmartContract* sc) {
	this->sc = sc;
	this->stack = new VmInstanceStack();
}

void VirtualMachine::createScInstance() {
	this->sc->createInstance(this);
}

void VirtualMachine::interpret(const UnicodeString* method) {

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

} /* namespace alinous */
