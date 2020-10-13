/*
 * AbstractCtrlInstruction.cpp
 *
 *  Created on: 2020/04/05
 *      Author: iizuka
 */

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

namespace alinous {

AbstractCtrlInstruction::AbstractCtrlInstruction() {

}

AbstractCtrlInstruction::~AbstractCtrlInstruction() {

}

ObjectReference* AbstractCtrlInstruction::getException() const noexcept {
	return nullptr;
}


} /* namespace alinous */
