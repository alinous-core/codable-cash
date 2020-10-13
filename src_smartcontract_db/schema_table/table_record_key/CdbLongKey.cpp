/*
 * CdbLongKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbLongKey.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbLongKey::CdbLongKey(const CdbLongKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_LONG) {
	this->value = inst.value;
}

CdbLongKey::CdbLongKey() : AbstractCdbKey(AbstractCdbKey::TYPE_LONG) {
	this->value = 0;
}

CdbLongKey::CdbLongKey(int64_t value) : AbstractCdbKey(AbstractCdbKey::TYPE_LONG) {
	this->value = value;
}


CdbLongKey::~CdbLongKey() {

}

AbstractBtreeKey* CdbLongKey::clone() const noexcept {
	return new CdbLongKey(*this);
}

int CdbLongKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	const CdbLongKey* cdbkey = dynamic_cast<const CdbLongKey*>(key);
	return this->value - cdbkey->value;
}

int CdbLongKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbLongKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);
	out->putLong(this->value);
}

void CdbLongKey::fromBinary(ByteBuffer* in) {
	this->value = in->getLong();
}

} /* namespace codablecash */
