/*
 * ExtPrimitiveObject.cpp
 *
 *  Created on: 2019/12/18
 *      Author: iizuka
 */

#include "ext_binary/ExtPrimitiveObject.h"

#include "instance/VmInstanceTypesConst.h"


namespace alinous {

ExtPrimitiveObject::ExtPrimitiveObject(UnicodeString* name, uint8_t type) : AbstractExtObject(name, type) {

}

ExtPrimitiveObject::~ExtPrimitiveObject() {

}


ExtPrimitiveObject* ExtPrimitiveObject::createBoolObject(UnicodeString* name, int8_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_BOOL);
}

ExtPrimitiveObject* ExtPrimitiveObject::createByteObject(UnicodeString* name, int8_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_BYTE);
}

ExtPrimitiveObject* ExtPrimitiveObject::createCharObject(UnicodeString* name, int16_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_CHAR);
}

ExtPrimitiveObject* ExtPrimitiveObject::createShortObject(UnicodeString* name, int16_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_SHORT);
}

ExtPrimitiveObject* ExtPrimitiveObject::createIntObject(UnicodeString* name, int32_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_INT);
}

ExtPrimitiveObject* ExtPrimitiveObject::createLongObject(UnicodeString* name, int64_t value) noexcept {
	return new ExtPrimitiveObject(name, VmInstanceTypesConst::REF_LONG);
}

} /* namespace alinous */
