/*
 * ExecControlManager.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm_ctrl/ExecControlManager.h"
#include "vm_ctrl/AbstractCtrlInstruction.h"


namespace alinous {

ExecControlManager::ExecControlManager() {
	this->instruction = nullptr;
}

ExecControlManager::~ExecControlManager() {
	delete this->instruction;
}

void ExecControlManager::setInstruction(AbstractCtrlInstruction* instruction) noexcept {
	delete this->instruction;
	this->instruction = instruction;
}

} /* namespace alinous */
