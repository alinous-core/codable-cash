/*
 * CdbLongKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbLongKey.h"

namespace codablecash {

CdbLongKey::CdbLongKey() : AbstractCdbKey(AbstractCdbKey::TYPE_LONG) {
	this->value = 0;
}

CdbLongKey::~CdbLongKey() {

}

AbstractBtreeKey* CdbLongKey::clone() const noexcept {
}

int CdbLongKey::compareTo(const AbstractBtreeKey* key) const noexcept {
}

int CdbLongKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbLongKey::toBinary(ByteBuffer* out) const {
}

void CdbLongKey::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
