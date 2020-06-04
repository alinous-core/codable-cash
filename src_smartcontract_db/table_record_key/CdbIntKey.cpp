/*
 * CdbIntKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbIntKey.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

CdbIntKey::CdbIntKey(const CdbIntKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_INT) {
	this->value = inst.value;
}

CdbIntKey::CdbIntKey() : AbstractCdbKey(AbstractCdbKey::TYPE_INT) {
	this->value = 0;
}

CdbIntKey::CdbIntKey(int32_t value) : AbstractCdbKey(AbstractCdbKey::TYPE_INT) {
	this->value = value;
}

CdbIntKey::~CdbIntKey() {

}

AbstractBtreeKey* CdbIntKey::clone() const noexcept {
	return new CdbIntKey(*this);
}

int CdbIntKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

	const CdbIntKey* cdbkey = dynamic_cast<const CdbIntKey*>(key);
	return this->value - cdbkey->value;
}

int CdbIntKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbIntKey::toBinary(ByteBuffer* out) const {
	out->putInt(this->type);
	out->putInt(this->value);
}

void CdbIntKey::fromBinary(ByteBuffer* in) {
	this->value = in->getInt();
}

} /* namespace codablecash */
