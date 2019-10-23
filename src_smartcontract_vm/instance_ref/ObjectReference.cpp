/*
 * ObjectReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/ObjectReference.h"

namespace alinous {

ObjectReference::ObjectReference(uint8_t type) : AbstractReference(type) {
	this->instance = nullptr;
}

ObjectReference::~ObjectReference() {

}

bool ObjectReference::isPrimitive() const noexcept {
	return false;
}

AbstractVmInstance* ObjectReference::getInstance() const noexcept {
	return this->instance;
}

void ObjectReference::setInstance(AbstractVmInstance* instance) noexcept {
	this->instance = instance;
}

} /* namespace alinous */
