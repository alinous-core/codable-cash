/*
 * AbstractExtObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/AbstractExtObject.h"

#include "base/UnicodeString.h"

#include "instance/VmInstanceTypesConst.h"
namespace alinous {

AbstractExtObject::AbstractExtObject(const UnicodeString* name, uint8_t type) {
	this->name = new UnicodeString(name);
	this->type = type;
}

AbstractExtObject::~AbstractExtObject() {
	delete this->name;
}

const UnicodeString* AbstractExtObject::getName() const noexcept {
	return this->name;
}

uint8_t AbstractExtObject::getType() const noexcept {
	return this->type;
}

bool AbstractExtObject::isNull() const noexcept {
	return false;
}

} /* namespace alinous */
