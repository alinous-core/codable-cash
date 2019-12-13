/*
 * VTableMethodEntry.cpp
 *
 *  Created on: 2019/11/30
 *      Author: iizuka
 */

#include "sc_analyze_functions/VTableMethodEntry.h"

#include "sc_declare/MethodDeclare.h"

namespace alinous {

VTableMethodEntry::VTableMethodEntry(MethodDeclare* method, int type) {
	this->method = method;
	this->type = type;
}

VTableMethodEntry::~VTableMethodEntry() {
}

const UnicodeString* VTableMethodEntry::getName() const noexcept {
	return this->method->getName();
}


} /* namespace alinous */
