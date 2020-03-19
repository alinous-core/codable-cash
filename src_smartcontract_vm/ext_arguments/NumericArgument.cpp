/*
 * NumericArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/NumericArgument.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

namespace alinous {

NumericArgument::NumericArgument() {

}

NumericArgument::~NumericArgument() {

}

AnalyzedType NumericArgument::getType() const noexcept {
}

AbstractVmInstance* NumericArgument::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
