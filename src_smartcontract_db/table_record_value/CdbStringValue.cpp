/*
 * CdbStringValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"

#include "table_record_key/CdbStringKey.h"

namespace codablecash {

CdbStringValue::CdbStringValue(const CdbStringValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = new UnicodeString(inst.value);
}

CdbStringValue::CdbStringValue() : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = nullptr;
}

CdbStringValue::CdbStringValue(const wchar_t* str) : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = new UnicodeString(str);
}

CdbStringValue::CdbStringValue(const UnicodeString* str) : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = new UnicodeString(str);
}

CdbStringValue::~CdbStringValue() {
	delete this->value;
}

int CdbStringValue::binarySize() const {
	int total = sizeof(int8_t);

	total += stringSize(this->value);

	return total;
}

void CdbStringValue::toBinary(ByteBuffer* out) const {
	out->put(this->type);

	putString(out, this->value);
}

void CdbStringValue::fromBinary(ByteBuffer* in) {
	this->value = getString(in);
}

int CdbStringValue::stringSize(UnicodeString* str) noexcept {
	return sizeof(uint32_t) + str->length() * sizeof(uint16_t);
}

void CdbStringValue::putString(ByteBuffer* out, UnicodeString* str) noexcept {
	uint32_t maxLoop = str->length();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = str->get(i);
		out->putChar(ch);
	}
}

AbstractCdbKey* CdbStringValue::toKey() const noexcept {
	return new CdbStringKey(this->value);
}

AbstractCdbValue* CdbStringValue::copy() const noexcept {
	return new CdbStringValue(*this);
}

UnicodeString* CdbStringValue::getString(ByteBuffer* in) noexcept {
	UnicodeString* ret = new UnicodeString(L"");
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = in->getChar();
		ret->append(ch);
	}

	return ret;
}


} /* namespace codablecash */
