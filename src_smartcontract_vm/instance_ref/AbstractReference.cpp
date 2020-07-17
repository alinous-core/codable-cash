/*
 * AbstractReference.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "instance_ref/AbstractReference.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString AbstractReference::NULL_STR(L"null");

AbstractReference::AbstractReference(IAbstractVmInstanceSubstance* owner, uint8_t type) : AbstractVmInstance(type), owner(owner) {

}

AbstractReference::~AbstractReference() {

}

bool AbstractReference::isPrimitive() const noexcept {
	return false;
}

bool AbstractReference::isReference() const noexcept {
	return true;
}

bool AbstractReference::isDom() const noexcept {
	return false;
}


void AbstractReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
}

IAbstractVmInstanceSubstance* AbstractReference::getOwner() const noexcept {
	return this->owner;
}

void AbstractReference::setOwner(IAbstractVmInstanceSubstance* owner) noexcept {
	this->owner = owner;
}

const UnicodeString* AbstractReference::toString() const noexcept {
	return &NULL_STR;
}

} /* namespace alinous */
