/*
 * ReturnControl.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm_ctrl/ReturnControl.h"

#include "vm_ctrl/ExecControlManager.h"
#include "vm_ctrl/BlockState.h"

namespace alinous {

ReturnControl::ReturnControl() : AbstractCtrlInstruction() {

}

ReturnControl::~ReturnControl() {

}

bool ReturnControl::control(ExecControlManager* ctrl, BlockState* state, CodeElement* lastElement) {
	int type = state->getType();
	if(type == BlockState::BLOCK_METHOD){
		ctrl->consumeInstruction();
	}

	return true;
}

} /* namespace alinous */
