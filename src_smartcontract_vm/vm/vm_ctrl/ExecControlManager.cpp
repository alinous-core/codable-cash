/*
 * ExecControlManager.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/AbstractCtrlInstruction.h"
#include "vm/vm_ctrl/BlockState.h"

#include "engine/sc/CodeElement.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_ctrl/ExceptionControl.h"

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

ObjectReference* ExecControlManager::getException() const noexcept {
	return this->instruction != nullptr ? this->instruction->getException() : nullptr;
}

void ExecControlManager::consumeException(VirtualMachine* vm) noexcept {
	ExceptionControl* exInstruction = dynamic_cast<ExceptionControl*>(this->instruction);

	exInstruction->releaseException(vm);
	consumeInstruction();
	doConsumeInstruction();
}

bool ExecControlManager::isExceptionThrown() const noexcept {
	ExceptionControl* exInstruction = dynamic_cast<ExceptionControl*>(this->instruction);

	return exInstruction != nullptr;
}


} /* namespace alinous */
