/*
 * VmStackManager.cpp
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#include "stack/VmStackManager.h"
#include "stack/VmStack.h"
namespace alinous {

VmStackManager::VmStackManager() {

}

VmStackManager::~VmStackManager() {
	this->list.deleteElements();
}

void VmStackManager::addStack(VmStack* stack) noexcept {
	this->list.addElement(stack);
}

void VmStackManager::popStack() noexcept {
	int pos = this->list.size() - 1;
	VmStack* stack = this->list.remove(pos);
	delete stack;
}

} /* namespace alinous */
