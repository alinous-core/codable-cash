/*
 * BlockState.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm/vm_ctrl/BlockState.h"

namespace alinous {

BlockState::BlockState(int type) {
	this->type = type;
}

BlockState::~BlockState() {

}

int BlockState::getType() const noexcept {
	return this->type;
}


} /* namespace alinous */
