/*
 * ObjectReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/ObjectReference.h"

#include "instance/VmClassInstance.h"

namespace alinous {

ObjectReference::ObjectReference(uint8_t type) : AbstractReference(type) {
	this->instance = nullptr;
}

ObjectReference::~ObjectReference() {

}

ObjectReference* ObjectReference::createObjectReference(VmClassInstance* clazzInst, VirtualMachine* vm) {
	ObjectReference* ref = new(vm) ObjectReference(AbstractVmInstance::REF_OBJ);
	ref->setInstance(clazzInst);

	return ref;
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

void ObjectReference::substitute(AbstractVmInstance* rightValue, VirtualMachine* vm) {
	// FIXME substitute
	assert(false);
}


} /* namespace alinous */
