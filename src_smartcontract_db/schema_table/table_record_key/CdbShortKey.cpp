/*
 * CdbShortKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "schema_table/table_record_key/CdbShortKey.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

CdbShortKey::CdbShortKey(const CdbShortKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_SHORT) {
	this->value = inst.value;
}

CdbShortKey::CdbShortKey(int16_t value) : AbstractCdbKey(AbstractCdbKey::TYPE_SHORT) {
	this->value = value;
}

CdbShortKey::CdbShortKey() : AbstractCdbKey(AbstractCdbKey::TYPE_SHORT) {
	this->value = 0;
}

CdbShortKey::~CdbShortKey() {

}

AbstractBtreeKey* CdbShortKey::clone() const noexcept {
	return new CdbShortKey(*this);
}

int CdbShortKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	const CdbShortKey* cdbkey = dynamic_cast<const CdbShortKey*>(key);
	return this->value - cdbkey->value;
}

int CdbShortKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbShortKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);
	out->putShort(this->value);
}

void CdbShortKey::fromBinary(ByteBuffer* in) {
	this->value = in->getShort();
}

} /* namespace codablecash */
