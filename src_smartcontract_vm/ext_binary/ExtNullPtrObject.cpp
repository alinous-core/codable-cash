/*
 * ExtNullPtrObject.cpp
 *
 *  Created on: 2020/03/28
 *      Author: iizuka
 */

#include "ext_binary/ExtNullPtrObject.h"

namespace alinous {

ExtNullPtrObject::ExtNullPtrObject(const UnicodeString* name, uint8_t type) : AbstractExtObject(name, type){
}

ExtNullPtrObject::~ExtNullPtrObject() {
}

bool ExtNullPtrObject::isNull() const noexcept {
	return true;
}

AbstractExtObject* ExtNullPtrObject::copy() const noexcept {
	return new ExtNullPtrObject(this->name, this->type);
}

} /* namespace alinous */
