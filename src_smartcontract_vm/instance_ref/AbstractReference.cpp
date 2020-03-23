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

IAbstractVmInstanceSubstance* AbstractReference::getInstance() noexcept {
	return this;
}

bool AbstractReference::isReference() const noexcept {
	return true;
}

void AbstractReference::substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm) {
}

IAbstractVmInstanceSubstance* AbstractReference::getOwner() const noexcept {
	return this->owner;
}



} /* namespace alinous */
