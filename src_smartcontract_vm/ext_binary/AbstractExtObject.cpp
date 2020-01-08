/*
 * AbstractExtObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/AbstractExtObject.h"

#include "base/UnicodeString.h"

namespace alinous {

AbstractExtObject::AbstractExtObject(UnicodeString* name) {
	this->name = new UnicodeString(name);
}

AbstractExtObject::~AbstractExtObject() {
	delete this->name;
}

const UnicodeString* AbstractExtObject::getName() const noexcept {
	return this->name;
}


} /* namespace alinous */
