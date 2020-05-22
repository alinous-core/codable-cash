/*
 * CdbByteKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbByteKey.h"

namespace codablecash {

CdbByteKey::CdbByteKey(const CdbByteKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_BYTE) {
	this->value = inst.value;
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
}

int CdbByteKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbByteKey::toBinary(ByteBuffer* out) const {
}

void CdbByteKey::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
