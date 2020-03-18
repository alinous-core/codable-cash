/*
 * StringConstHolder.cpp
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#include "instance_ref_static/StringConstHolder.h"

namespace alinous {

StringConstHolder::StringConstHolder() {

}

StringConstHolder::~StringConstHolder() {

}

VmStringInstance* StringConstHolder::newStringConstInstance(const UnicodeString* str, VirtualMachine* vm) {

}

void StringConstHolder::removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept {

}

} /* namespace alinous */
