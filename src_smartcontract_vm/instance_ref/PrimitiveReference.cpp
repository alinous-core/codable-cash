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

#include "sc_analyze/AnalyzedType.h"
namespace alinous {

PrimitiveReference::PrimitiveReference(uint8_t type) : AbstractReference(nullptr, type) {
	this->data = nullptr;
	this->malloc = nullptr;
}

PrimitiveReference::~PrimitiveReference() {
	if(this->data != nullptr){
		this->malloc->releaseArray(this->data);
	}
}

bool PrimitiveReference::getBoolValue() const noexcept {
	return getIntValue() > 0;
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

int PrimitiveReference::valueCompare(IAbstractVmInstanceSubstance* right) {
	int64_t ret = 0;

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(right);
	if(ref == nullptr){
		return -1;
	}

	uint8_t cmpType = this->type >= ref->type ? this->type : ref->type;

	switch(cmpType){
	case VmInstanceTypesConst::REF_BYTE:
		return valueCompare8(ref);
	case VmInstanceTypesConst::REF_SHORT:
	case VmInstanceTypesConst::REF_CHAR:
		return valueCompare16(ref);
	case VmInstanceTypesConst::REF_INT:
		return valueCompare32(ref);
	case VmInstanceTypesConst::REF_LONG:
		return valueCompare64(ref);
	default:
		break;
	}

	return -1;
}

int PrimitiveReference::valueCompare8(PrimitiveReference* right) {
	int8_t leftv = getByteValue();
	int8_t rightv = right->getByteValue();

	return leftv - rightv;
}

int PrimitiveReference::valueCompare16(PrimitiveReference* right) {
	int16_t leftv = getShortValue();
	int16_t rightv = right->getShortValue();

	return leftv - rightv;
}

int PrimitiveReference::valueCompare32(PrimitiveReference* right) {
	int32_t leftv = getIntValue();
	int32_t rightv = right->getIntValue();

	return leftv - rightv;
}

AbstractReference* PrimitiveReference::wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) {
	/*PrimitiveReference* newInst = nullptr;

	switch(this->type){
	case VmInstanceTypesConst::REF_BOOL:
		newInst = createBoolReference(vm, getBoolValue() ? 1 : 0);
		break;
	case VmInstanceTypesConst::REF_BYTE:
		newInst = createByteReference(vm, getByteValue());
		break;
	case VmInstanceTypesConst::REF_CHAR:
		newInst = createCharReference(vm, getCharValue());
		break;
	case VmInstanceTypesConst::REF_SHORT:
		newInst = createShortReference(vm, getShortValue());
		break;
	case VmInstanceTypesConst::REF_INT:
		newInst = createIntReference(vm, getIntValue());
		break;
	case VmInstanceTypesConst::REF_LONG:
	default:
		newInst = createLongReference(vm, getLongValue());
		break;
	}

	return newInst;*/

	return copy(vm);
}

uint8_t PrimitiveReference::getInstType() const noexcept {
	return getType();
}

AnalyzedType PrimitiveReference::getRuntimeType() const noexcept {
	uint8_t type = getType();

	switch(type){
	case VmInstanceTypesConst::REF_BOOL:
		return AnalyzedType(AnalyzedType::TYPE_BOOL);
	case VmInstanceTypesConst::REF_BYTE:
		return AnalyzedType(AnalyzedType::TYPE_BYTE);
	case VmInstanceTypesConst::REF_CHAR:
		return AnalyzedType(AnalyzedType::TYPE_CHAR);
	case VmInstanceTypesConst::REF_SHORT:
		return AnalyzedType(AnalyzedType::TYPE_SHORT);
	case VmInstanceTypesConst::REF_INT:
		return AnalyzedType(AnalyzedType::TYPE_INT);
	case VmInstanceTypesConst::REF_LONG:
	default:
		break;
	}

	return AnalyzedType(AnalyzedType::TYPE_LONG);
}

const VMemList<AbstractReference>* PrimitiveReference::getInstReferences() const noexcept {
	return getReferences();
}

int PrimitiveReference::instHashCode() const noexcept {
	return hashCode();
}

bool PrimitiveReference::instIsNull() const noexcept {
	return isNull();
}

int PrimitiveReference::instValueCompare(IAbstractVmInstanceSubstance* right) {
	return valueCompare(right);
}

AbstractExtObject* PrimitiveReference::instToClassExtObject(const UnicodeString* name, VTableRegistory* table) {
	return toClassExtObject(name, table);
}

bool PrimitiveReference::instIsPrimitive() const noexcept {
	return isPrimitive();
}

IAbstractVmInstanceSubstance* PrimitiveReference::getInstance() noexcept {
	return this;
}

bool PrimitiveReference::isStaticConst() const noexcept {
	return false;
}

int PrimitiveReference::valueCompare64(PrimitiveReference* right) {
	int64_t leftv = getLongValue();
	int64_t rightv = right->getLongValue();

	return leftv - rightv;
}


void PrimitiveReference::setLongValue(int64_t value) noexcept {
	*((int64_t*)this->data) = value;
}


bool PrimitiveReference::isPrimitive() const noexcept {
	return true;
}

void PrimitiveReference::substitute(IAbstractVmInstanceSubstance* rightValue,	VirtualMachine* vm) {
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
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setIntValue(value > 0 ? 1 : 0);

	return ref;
}

PrimitiveReference* PrimitiveReference::createIntReference(VirtualMachine* vm, int32_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_INT);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setIntValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createByteReference(VirtualMachine* vm, int8_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_BYTE);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setByteValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createCharReference(VirtualMachine* vm,	int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_CHAR);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setCharValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createShortReference(VirtualMachine* vm, int16_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_SHORT);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setShortValue(value);

	return ref;
}

PrimitiveReference* PrimitiveReference::createLongReference(VirtualMachine* vm,	int64_t value) {
	PrimitiveReference* ref = new(vm) PrimitiveReference(VmInstanceTypesConst::REF_LONG);

	ref->malloc = vm->getAlloc();
	ref->data = ref->malloc->mallocPtrArray(getDataSize(ref->type));
	ref->setLongValue(value);

	return ref;
}

size_t PrimitiveReference::getDataSize(int8_t type) noexcept {
	size_t ret = 0;

	switch(type){
	case VmInstanceTypesConst::REF_BYTE:
		ret = sizeof(int8_t);
		break;
	case VmInstanceTypesConst::REF_CHAR:
	case VmInstanceTypesConst::REF_SHORT:
		ret = sizeof(int16_t);
		break;
	case VmInstanceTypesConst::REF_LONG:
		ret = sizeof(int64_t);
		break;
	case VmInstanceTypesConst::REF_BOOL:
	case VmInstanceTypesConst::REF_INT:
	default:
		ret = sizeof(int32_t);
		break;
	}

	return ret;
}

PrimitiveReference* PrimitiveReference::copy(VirtualMachine* vm) const noexcept {
	PrimitiveReference* ref = new(vm) PrimitiveReference(this->type);

	size_t size = this->getDataSize(this->type);

	ref->malloc = vm->getAlloc();
	ref->data = this->malloc->mallocPtrArray(size);

	Mem::memcpy(ref->data, this->data, size);

	return ref;
}

} /* namespace alinous */
