/*
 * ExtPrimitiveObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/ExtPrimitiveObject.h"

#include "instance/VmInstanceTypesConst.h"

#include "osenv/memory.h"


namespace alinous {

ExtPrimitiveObject::ExtPrimitiveObject(const UnicodeString* name, uint8_t type) : AbstractExtObject(name, type) {
	Mem::memset(this->data, 0, sizeof(this->data));

}

ExtPrimitiveObject::~ExtPrimitiveObject() {

}


ExtPrimitiveObject* ExtPrimitiveObject::createBoolObject(const UnicodeString* name, int8_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_BOOL);
	obj->setBoolValue(value > 0);

	return obj;
}

ExtPrimitiveObject* ExtPrimitiveObject::createByteObject(const UnicodeString* name, int8_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_BYTE);
	obj->setByteValue(value);

	return obj;
}

ExtPrimitiveObject* ExtPrimitiveObject::createCharObject(const UnicodeString* name, int16_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_CHAR);
	obj->setCharValue(value);

	return obj;
}

ExtPrimitiveObject* ExtPrimitiveObject::createShortObject(const UnicodeString* name, int16_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_SHORT);
	obj->setShortValue(value);

	return obj;
}

ExtPrimitiveObject* ExtPrimitiveObject::createIntObject(const UnicodeString* name, int32_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_INT);
	obj->setIntValue(value);

	return obj;
}

ExtPrimitiveObject* ExtPrimitiveObject::createLongObject(const UnicodeString* name, int64_t value) noexcept {
	ExtPrimitiveObject* obj = new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_LONG);
	obj->setLongValue(value);

	return obj;
}

int32_t ExtPrimitiveObject::getIntValue() const noexcept {
	return *((int32_t*)this->data);
}

void ExtPrimitiveObject::setIntValue(int32_t value) noexcept {
	*((int32_t*)this->data) = value;
}

bool ExtPrimitiveObject::getBoolValue() const noexcept {
	return *((int32_t*)this->data) == 1;
}

void ExtPrimitiveObject::setBoolValue(bool value) noexcept {
	int32_t iv = value ? 1 : 0;
	*((int32_t*)this->data) = iv;
}

int8_t ExtPrimitiveObject::getByteValue() const noexcept {
	return *((int8_t*)this->data);
}

void ExtPrimitiveObject::setByteValue(int8_t value) noexcept {
	*((int8_t*)this->data) = value;
}

int16_t ExtPrimitiveObject::getShortValue() const noexcept {
	return *((int16_t*)this->data);
}

void ExtPrimitiveObject::setShortValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int16_t ExtPrimitiveObject::getCharValue() const noexcept {
	return *((int16_t*)this->data);
}

void ExtPrimitiveObject::setCharValue(int16_t value) noexcept {
	*((int16_t*)this->data) = value;
}

int64_t ExtPrimitiveObject::getLongValue() const noexcept {
	return *((int64_t*)this->data);
}

void ExtPrimitiveObject::setLongValue(int64_t value) noexcept {
	*((int64_t*)this->data) = value;
}

} /* namespace alinous */
