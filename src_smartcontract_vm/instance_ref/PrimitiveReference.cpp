/*
 * PrimitiveReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/PrimitiveReference.h"
#include "instance_parts/VmMalloc.h"

#include "vm/VirtualMachine.h"

namespace alinous {

PrimitiveReference::PrimitiveReference(uint8_t type) : AbstractReference(type) {
	this->data = nullptr;
}

PrimitiveReference::~PrimitiveReference() {

}

PrimitiveReference* PrimitiveReference::createIntReference(VirtualMachine* vm, int32_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_INT);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int32_t));
	ref->setIntValue(value);

	return ref;
}

int32_t PrimitiveReference::getIntValue() noexcept {
	return *((int32_t*)this->data);
}

void PrimitiveReference::setIntValue(int32_t value) noexcept {
	*((int32_t*)this->data) = value;
}

} /* namespace alinous */
