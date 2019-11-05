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

bool alinous::AbstractReference::isPrimitive() const noexcept {
	return false;
}

AbstractVmInstance* alinous::AbstractReference::getInstance() noexcept {
	return this;
}

bool alinous::AbstractReference::isReference() const noexcept {
	return true;
}

} /* namespace alinous */
