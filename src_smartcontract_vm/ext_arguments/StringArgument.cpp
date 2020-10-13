/*
 * StringArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/StringArgument.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base/UnicodeString.h"

#include "instance/instance_string/VmStringInstance.h"


namespace alinous {

StringArgument::StringArgument(const UnicodeString* str) {
	this->value = new UnicodeString(str);
}

StringArgument::~StringArgument() {
	delete this->value;
}

AnalyzedType StringArgument::getType() const noexcept {
	return AnalyzedType(AnalyzedType::TYPE_STRING);
}

AbstractVmInstance* StringArgument::interpret(VirtualMachine* vm) {
	VmStringInstance* inst = new(vm) VmStringInstance(vm, this->value);

	return inst;
}

} /* namespace alinous */
