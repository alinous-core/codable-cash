/*
 * NullArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/NullArgument.h"

#include "engine/sc_analyze/AnalyzedType.h"

namespace alinous {

NullArgument::NullArgument(const AnalyzedType* type) {
	this->atype = new AnalyzedType(*type);
}

NullArgument::~NullArgument() {
	delete this->atype;
}

AnalyzedType NullArgument::getType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* NullArgument::interpret(VirtualMachine* vm) {
	return nullptr;
}

} /* namespace alinous */
