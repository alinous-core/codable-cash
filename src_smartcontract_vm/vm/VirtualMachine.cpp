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

namespace alinous {

VirtualMachine::VirtualMachine(uint64_t memCapacity) {
	this->stack = nullptr;
	this->sc = nullptr;
	this->memory = new VmMemoryManager(memCapacity);
}

VirtualMachine::~VirtualMachine() {
	delete this->sc;
	delete this->stack;
	delete this->memory;
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


void VirtualMachine::analyze() {
	this->sc->analyze(this);
}

} /* namespace alinous */

