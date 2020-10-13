/*
 * CdbStringKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbStringKey.h"

#include "table_record_value/CdbStringValue.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

UnicodeString::ValueCompare CdbStringKey::cmp;

CdbStringKey::CdbStringKey(const CdbStringKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_STRING) {
	this->value = new UnicodeString(inst.value);
}

CdbStringKey::CdbStringKey(const UnicodeString* str) : AbstractCdbKey(AbstractCdbKey::TYPE_STRING) {
	this->value = new UnicodeString(str);
}

CdbStringKey::CdbStringKey() : AbstractCdbKey(AbstractCdbKey::TYPE_STRING) {
	this->value = nullptr;
}

CdbStringKey::~CdbStringKey() {
	delete this->value;
}

AbstractBtreeKey* CdbStringKey::clone() const noexcept {
	return new CdbStringKey(*this);
}

int CdbStringKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	const CdbStringKey* strkey = dynamic_cast<const CdbStringKey*>(key);

	return CdbStringKey::cmp(this->value, strkey->value);
}

int CdbStringKey::binarySize() const {
	int total = sizeof(uint32_t);
	total += CdbStringValue::stringSize(this->value);

	return total;
}

void CdbStringKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);

	CdbStringValue::putString(out, this->value);
}

void CdbStringKey::fromBinary(ByteBuffer* in) {
	this->value = CdbStringValue::getString(in);
}

} /* namespace codablecash */
