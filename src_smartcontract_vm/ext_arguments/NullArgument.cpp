/*
 * NullArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/NullArgument.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

NullArgument::NullArgument(const AnalyzedType* type) {
	this->atype = new AnalyzedType(*type);
}

NullArgument::~NullArgument() {

}

AnalyzedType NullArgument::getType() const noexcept {

}

AbstractVmInstance* NullArgument::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
