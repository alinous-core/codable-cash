/*
 * StringArgument.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "ext_arguments/StringArgument.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base/UnicodeString.h"

namespace alinous {

StringArgument::StringArgument(const UnicodeString* str) {
	this->value = new UnicodeString(str);
}

StringArgument::~StringArgument() {

}

AnalyzedType StringArgument::getType() const noexcept {
}

AbstractVmInstance* StringArgument::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
