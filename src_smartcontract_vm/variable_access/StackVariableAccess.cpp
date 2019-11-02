/*
 * StackVariableAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/StackVariableAccess.h"

namespace alinous {

StackVariableAccess::StackVariableAccess(int stackPos, int pos) {
	this->stackPos = stackPos;
	this->pos = pos;
}

StackVariableAccess::~StackVariableAccess() {
}

} /* namespace alinous */
