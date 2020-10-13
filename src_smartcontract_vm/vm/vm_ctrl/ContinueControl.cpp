/*
 * ContinueControl.cpp
 *
 *  Created on: 2020/04/08
 *      Author: iizuka
 */

#include "vm/vm_ctrl/ContinueControl.h"

#include "vm/vm_ctrl/BlockState.h"
#include "vm/vm_ctrl/ExecControlManager.h"


namespace alinous {

ContinueControl::ContinueControl() {

}

ContinueControl::~ContinueControl() {

}

int ContinueControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {
	int type = state->getType();
	if(type == BlockState::BLOCK_DO_WHILE || type == BlockState::BLOCK_FOR || type == BlockState::BLOCK_WHILE){
		ctrl->consumeInstruction();
	}

	return AbstractCtrlInstruction::RET_CONTINUE;
}

} /* namespace alinous */
