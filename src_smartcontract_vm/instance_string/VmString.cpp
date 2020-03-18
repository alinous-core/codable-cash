/*
 * VmString.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "instance_string/VmString.h"

#include "base/UnicodeString.h"

#include "vm/VirtualMachine.h"

namespace alinous {

VmString::VmString(VirtualMachine* vm, const UnicodeString* ptr) {
	this->buff =  new(vm) VMemPrimitiveList<wchar_t>(vm, ptr->length() + 1);
	this->__hashCode = 0;

	int length = ptr->length();
	for(int i = 0; i != length; ++i){
		wchar_t ch = ptr->charAt(i);
		__append(ch);
	}

	__closeString();
}

VmString::~VmString() {
	delete this->buff;
}

VmString* VmString::__append(wchar_t ch) noexcept {
	this->buff->addElement(ch);

	return this;
}

int VmString::length() const noexcept {
	return this->buff->size();
}

wchar_t VmString::charAt(int index) const noexcept {
	return this->buff->get(index);
}

void VmString::__closeString() noexcept {
	this->buff->addElement(L'\0');
	this->buff->backLast();

	const int count = length();
    if (count == 0) {
    	this->__hashCode = 0;
        return;
    }
    int hash = 0;
    for (int i = 0; i < count; i++) {
        hash = charAt(i) + ((hash << 5) - hash);
    }
    this->__hashCode = hash;
}

} /* namespace alinous */
