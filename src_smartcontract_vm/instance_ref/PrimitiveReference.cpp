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

int32_t PrimitiveReference::getIntValue() const noexcept {
	return *((int32_t*)this->data);
}
void PrimitiveReference::setIntValue(int32_t value) noexcept {
	*((int32_t*)this->data) = value;
}

int8_t PrimitiveReference::getByteValue() const noexcept {
	return *((int8_t*)this->data);
}

void PrimitiveReference::setByteValue(int8_t value) noexcept {
	*((int8_t*)this->data) = value;
}

int16_t PrimitiveReference::getShortValue() const noexcept {
	return *((int16_t*)this->data);
}

void PrimitiveReference::setShortValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int16_t PrimitiveReference::getCharValue() const noexcept {
	return *((int16_t*)this->data);
}

void PrimitiveReference::setCharValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int64_t PrimitiveReference::getLongValue() const noexcept {
	return *((int64_t*)this->data);
}

bool PrimitiveReference::isPrimitive() const noexcept {
	return true;
}

void PrimitiveReference::setLongValue(int64_t value) noexcept {
	*((int64_t*)this->data) = value;
}

PrimitiveReference* PrimitiveReference::createIntReference(VirtualMachine* vm, int32_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_INT);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int32_t));
	ref->setIntValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createByteReference(VirtualMachine* vm, int8_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_BYTE);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int8_t));
	ref->setByteValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createCharReference(VirtualMachine* vm,	int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_CHAR);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int16_t));
	ref->setCharValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createShortReference(VirtualMachine* vm, int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_SHORT);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int16_t));
	ref->setShortValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createLongReference(VirtualMachine* vm,	int64_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(AbstractVmInstance::REF_LONG);

	VmMalloc* alloc = vm->getAlloc();
	ref->data = alloc->mallocPtrArray(sizeof(int64_t));
	ref->setLongValue(value);

	return ref;
}


} /* namespace alinous */
