/*
 * AbstractReference.cpp
 *
 *  Created on: 2019/05/24
 *      Author: iizuka
 */

#include "instance_ref/AbstractReference.h"

namespace alinous {

AbstractReference::AbstractReference(uint8_t type) : AbstractVmInstance(type) {

}

AbstractReference::~AbstractReference() {

}

bool AbstractReference::isPrimitive() const noexcept {
	return false;
}

AbstractVmInstance* AbstractReference::getInstance() noexcept {
	return this;
}

bool AbstractReference::isReference() const noexcept {
	return true;
}

void AbstractReference::substitute(AbstractVmInstance* rightValue, VirtualMachine* vm) {
}


} /* namespace alinous */
