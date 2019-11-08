/*
 * AbstractVariableInstraction.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

AbstractVariableInstraction::AbstractVariableInstraction() {

}

AbstractVariableInstraction::~AbstractVariableInstraction() {

}

AbstractVmInstance* AbstractVariableInstraction::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	// FIXME interpret
	return nullptr;
}

} /* namespace alinous */
