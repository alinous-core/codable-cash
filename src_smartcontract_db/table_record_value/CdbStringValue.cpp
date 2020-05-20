/*
 * CdbStringValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"
#include "base/UnicodeString.h"

namespace codablecash {

CdbStringValue::CdbStringValue(const CdbStringValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = new UnicodeString(inst.value);
}

CdbStringValue::CdbStringValue() : AbstractCdbValue(AbstractCdbValue::TYPE_STRING) {
	this->value = nullptr;
}

CdbStringValue::~CdbStringValue() {
	delete this->value;
}
/*
int CdbStringValue::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

	const CdbStringValue* strkey = dynamic_cast<const CdbStringValue*>(key);

	return CdbStringValue::cmp(this->value, strkey->value);
}

AbstractBtreeKey* CdbStringValue::clone() const noexcept {
	return new CdbStringValue(*this);
}*/

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

int CdbStringValue::stringSize(UnicodeString* str) const noexcept {
	return sizeof(uint32_t) + str->length() * sizeof(uint16_t);
}

void CdbStringValue::putString(ByteBuffer* out, UnicodeString* str) const noexcept {
	uint32_t maxLoop = str->length();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = str->get(i);
		out->putChar(ch);
	}
}

UnicodeString* CdbStringValue::getString(ByteBuffer* in) const noexcept {
	UnicodeString* ret = new UnicodeString(L"");
	uint32_t maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		wchar_t ch = in->getChar();
		ret->append(ch);
	}

	return ret;
}


} /* namespace codablecash */
