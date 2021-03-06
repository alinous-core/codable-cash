/*
 * CdbByteKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "schema_table/record/table_record_key/CdbByteKey.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbByteKey::CdbByteKey(const CdbByteKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_BYTE) {
	this->value = inst.value;
}

CdbByteKey::CdbByteKey(int8_t value) : AbstractCdbKey(AbstractCdbKey::TYPE_BYTE) {
	this->value = value;
}

CdbByteKey::CdbByteKey() : AbstractCdbKey(AbstractCdbKey::TYPE_BYTE) {
	this->value = 0;
}

CdbByteKey::~CdbByteKey() {

}

AbstractBtreeKey* CdbByteKey::clone() const noexcept {
	return new CdbByteKey(*this);
}

int CdbByteKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	const CdbByteKey* cdbkey = dynamic_cast<const CdbByteKey*>(key);
	return this->value - cdbkey->value;
}

int CdbByteKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbByteKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);
	out->put(this->value);
}

void CdbByteKey::fromBinary(ByteBuffer* in) {
	this->value = in->get();
}

} /* namespace codablecash */
