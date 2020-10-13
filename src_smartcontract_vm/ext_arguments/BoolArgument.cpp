/*
 * BoolArgument.cpp
 *
 *  Created on: 2020/03/19
 *      Author: iizuka
 */

#include "ext_arguments/BoolArgument.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"

namespace alinous {

BoolArgument::BoolArgument(bool value) {
	this->value = value;
}

BoolArgument::~BoolArgument() {

}

AnalyzedType BoolArgument::getType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

AbstractVmInstance* BoolArgument::interpret(VirtualMachine* vm) {
	PrimitiveReference* inst = PrimitiveReference::createBoolReference(vm, this->value);

	return inst;
}

} /* namespace alinous */
