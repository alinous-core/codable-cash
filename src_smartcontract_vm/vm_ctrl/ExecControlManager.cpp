/*
 * ExecControlManager.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm_ctrl/ExecControlManager.h"
#include "vm_ctrl/AbstractCtrlInstruction.h"
#include "vm_ctrl/BlockState.h"

#include "sc/CodeElement.h"

namespace alinous {

ExecControlManager::ExecControlManager() {
	this->instruction = nullptr;
	this->instruction2Consume = nullptr;
}

ExecControlManager::~ExecControlManager() {
	delete this->instruction;
	delete this->instruction2Consume;
}

void ExecControlManager::setInstruction(AbstractCtrlInstruction* instruction) noexcept {
	delete this->instruction;
	this->instruction = instruction;
}

void ExecControlManager::consumeInstruction() noexcept {
	this->instruction2Consume = this->instruction;
	this->instruction = nullptr;
}

void ExecControlManager::doConsumeInstruction() noexcept {
	delete this->instruction2Consume;
	this->instruction2Consume = nullptr;
}

int ExecControlManager::checkStatementCtrl(BlockState* state, CodeElement* lastElement) noexcept {
	if(this->instruction != nullptr){
		int result = this->instruction->control(this, state, lastElement);
		doConsumeInstruction();

		return result;
	}

	return AbstractCtrlInstruction::RET_NONE;
}

} /* namespace alinous */
