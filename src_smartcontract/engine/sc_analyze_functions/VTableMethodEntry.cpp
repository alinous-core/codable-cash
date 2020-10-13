/*
 * VTableMethodEntry.cpp
 *
 *  Created on: 2019/11/30
 *      Author: iizuka
 */

#include "engine/sc_analyze_functions/VTableMethodEntry.h"

#include "lang/sc_declare/MethodDeclare.h"

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

MethodDeclare* VTableMethodEntry::getMethod() const noexcept {
	return this->method;
}

bool VTableMethodEntry::isVirtual() const noexcept {
	return (this->type == METHOD_VIRTUAL || this->type == METHOD_VIRTUAL_SUPER) && !isStatic();
}

bool VTableMethodEntry::isStatic() const noexcept {
	return this->method->isStatic();
}



} /* namespace alinous */
