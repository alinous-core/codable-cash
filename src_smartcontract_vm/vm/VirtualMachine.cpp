/*
 * VirtualMachine.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#include "vm/VirtualMachine.h"
#include "instance/VmInstanceStack.h"
#include "sc/SmartContract.h"

namespace alinous {

VirtualMachine::VirtualMachine() {
	this->stack = nullptr;
	this->sc = nullptr;
}

VirtualMachine::~VirtualMachine() {
	if(this->sc){
		delete this->sc;
	}
	if(this->stack){
		delete this->stack;
	}
}

void VirtualMachine::loadSmartContract(SmartContract* sc) {
	this->sc = sc;
	this->stack = new VmInstanceStack();
}

} /* namespace alinous */
