/*
 * CdbBinaryObject.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "engine/CdbBinaryObject.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "engine/CdbException.h"

namespace codablecash {

CdbBinaryObject::CdbBinaryObject() {
}

CdbBinaryObject::~CdbBinaryObject() {

}
int CdbBinaryObject::stringSize(UnicodeString* str) const noexcept {
	return sizeof(uint32_t) + str->length() * sizeof(uint16_t);
}

void CdbBinaryObject::putString(ByteBuffer* out, UnicodeString* str) const noexcept {
	uint32_t maxLoop = str->length();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = str->get(i);
		out->putChar(ch);
	}
}
UnicodeString* CdbBinaryObject::getString(ByteBuffer* in) const noexcept {
	UnicodeString* ret = new UnicodeString(L"");
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = in->getChar();
		ret->append(ch);
	}

	return ret;
}

void CdbBinaryObject::checkNotNull(CdbBinaryObject* object) const {
	if(object == nullptr){
		throw new CdbException(L"Null pointer is not allowed.", __FILE__, __LINE__);
	}
}

void CdbBinaryObject::checkNotNull(UnicodeString* object) const {
	if(object == nullptr){
		throw new CdbException(L"Null pointer is not allowed.", __FILE__, __LINE__);
	}
}

void CdbBinaryObject::checkNotNull(TableIdentifier* object) const {
	if(object == nullptr){
		throw new CdbException(L"Null pointer is not allowed.", __FILE__, __LINE__);
	}
}


} /* namespace codablecash */
