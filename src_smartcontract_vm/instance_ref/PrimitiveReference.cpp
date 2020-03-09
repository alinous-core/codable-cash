/*
 * PrimitiveReference.cpp
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#include "instance_ref/PrimitiveReference.h"
#include "instance_parts/VmMalloc.h"

#include "vm/VirtualMachine.h"

#include "instance/VmInstanceTypesConst.h"

#include "ext_binary/ExtPrimitiveObject.h"

namespace alinous {

PrimitiveReference::PrimitiveReference(uint8_t type) : AbstractReference(type) {
	this->data = nullptr;
	this->malloc = nullptr;
}

PrimitiveReference::~PrimitiveReference() {
	if(this->data != nullptr){
		this->malloc->releaseArray(this->data);
	}
}

int32_t PrimitiveReference::getIntValue() const noexcept {
	int64_t ret = 0;

	switch(this->type){
	case VmInstanceTypesConst::REF_BYTE:
		ret = *((int8_t*)this->data);
		break;
	case VmInstanceTypesConst::REF_SHORT:
	case VmInstanceTypesConst::REF_CHAR:
		ret = *((int16_t*)this->data);
		break;
	default:
		ret = *((int32_t*)this->data);
		break;
	}

	return ret;
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
	if(this->type == VmInstanceTypesConst::REF_BYTE){
		return *((int8_t*)this->data);
	}

	return *((int16_t*)this->data);
}

void PrimitiveReference::setShortValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int16_t PrimitiveReference::getCharValue() const noexcept {
	if(this->type == VmInstanceTypesConst::REF_BYTE){
		return *((int8_t*)this->data);
	}

	return *((int16_t*)this->data);
}

void PrimitiveReference::setCharValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int64_t PrimitiveReference::getLongValue() const noexcept {
	int64_t ret = 0;

	switch(this->type){
	case VmInstanceTypesConst::REF_BYTE:
		ret = *((int8_t*)this->data);
		break;
	case VmInstanceTypesConst::REF_SHORT:
	case VmInstanceTypesConst::REF_CHAR:
		ret = *((int16_t*)this->data);
		break;
	case VmInstanceTypesConst::REF_BOOL:
	case VmInstanceTypesConst::REF_INT:
		ret = *((int32_t*)this->data);
		break;
	default:
		ret = *((int64_t*)this->data);
		break;
	}

	return ret;
}

int PrimitiveReference::valueCompare(const AbstractVmInstance* right) const {
	// FIXME compare
}

void PrimitiveReference::setLongValue(int64_t value) noexcept {
	*((int64_t*)this->data) = value;
}


bool PrimitiveReference::isPrimitive() const noexcept {
	return true;
}

void PrimitiveReference::substitute(AbstractVmInstance* rightValue,	VirtualMachine* vm) {
	uint8_t type = getType();
	PrimitiveReference* rightRef = dynamic_cast<PrimitiveReference*>(rightValue);
	assert(rightRef != nullptr);

	switch(type){
	case VmInstanceTypesConst::REF_BOOL:
		setIntValue(rightRef->getIntValue());
		break;
	case VmInstanceTypesConst::REF_BYTE:
		setByteValue(rightRef->getByteValue());
		break;
	case VmInstanceTypesConst::REF_CHAR:
		setCharValue(rightRef->getCharValue());
		break;
	case VmInstanceTypesConst::REF_SHORT:
		setShortValue(rightRef->getShortValue());
		break;
	case VmInstanceTypesConst::REF_INT:
		setIntValue(rightRef->getIntValue());
		break;
	case VmInstanceTypesConst::REF_LONG:
	default:
		setLongValue(rightRef->getLongValue());
		break;
	}

}

AbstractExtObject* PrimitiveReference::toClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	uint8_t type = getType();

	AbstractExtObject* extObj = nullptr;
	switch(type){
	case VmInstanceTypesConst::REF_BOOL:
		extObj = ExtPrimitiveObject::createBoolObject(name, getByteValue() == 1);
		break;
	case VmInstanceTypesConst::REF_BYTE:
		extObj = ExtPrimitiveObject::createByteObject(name, getByteValue());
		break;
	case VmInstanceTypesConst::REF_CHAR:
		extObj = ExtPrimitiveObject::createCharObject(name, getCharValue());
		break;
	case VmInstanceTypesConst::REF_SHORT:
		extObj = ExtPrimitiveObject::createShortObject(name, getShortValue());
		break;
	case VmInstanceTypesConst::REF_INT:
		extObj = ExtPrimitiveObject::createIntObject(name, getIntValue());
		break;
	case VmInstanceTypesConst::REF_LONG:
	default:
		extObj = ExtPrimitiveObject::createLongObject(name, getLongValue());
		break;
	}

	return extObj;
}


PrimitiveReference* PrimitiveReference::createBoolReference(VirtualMachine* vm,	int8_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_BOOL);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int32_t));
	ref->setIntValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createIntReference(VirtualMachine* vm, int32_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_INT);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int32_t));
	ref->setIntValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createByteReference(VirtualMachine* vm, int8_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_BYTE);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int8_t));
	ref->setByteValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createCharReference(VirtualMachine* vm,	int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_CHAR);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int16_t));
	ref->setCharValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createShortReference(VirtualMachine* vm, int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_SHORT);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int16_t));
	ref->setShortValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createLongReference(VirtualMachine* vm,	int64_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_LONG);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(sizeof(int64_t));
	ref->setLongValue(value);

	return ref;
}


} /* namespace alinous */
