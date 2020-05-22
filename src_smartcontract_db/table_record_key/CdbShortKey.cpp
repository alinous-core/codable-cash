/*
 * CdbShortKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbShortKey.h"

namespace codablecash {

CdbShortKey::CdbShortKey(const CdbShortKey& inst) : AbstractCdbKey(AbstractCdbKey::TYPE_SHORT) {
	this->value = inst.value;
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
}

int CdbShortKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbShortKey::toBinary(ByteBuffer* out) const {
}

void CdbShortKey::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
