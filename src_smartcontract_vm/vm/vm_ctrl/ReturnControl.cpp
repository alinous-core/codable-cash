/*
 * ReturnControl.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm/vm_ctrl/ReturnControl.h"

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/BlockState.h"

namespace alinous {

ReturnControl::ReturnControl() : AbstractCtrlInstruction() {

}

ReturnControl::~ReturnControl() {

}

int ReturnControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {
	int type = state->getType();
	if(type == BlockState::BLOCK_METHOD){
		ctrl->consumeInstruction();
	}

	return AbstractCtrlInstruction::RET_BREAK;
}

} /* namespace alinous */
