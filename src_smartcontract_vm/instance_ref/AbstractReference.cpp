/*
 * AbstractReference.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "instance_ref/AbstractReference.h"

namespace alinous {

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

void AbstractReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
}

IAbstractVmInstanceSubstance* AbstractReference::getOwner() const noexcept {
	return this->owner;
}

void AbstractReference::setOwner(IAbstractVmInstanceSubstance* owner) noexcept {
	this->owner = owner;
}


} /* namespace alinous */
