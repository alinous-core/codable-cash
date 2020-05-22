/*
 * CdbIntKey.cpp
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#include "table_record_key/CdbIntKey.h"

namespace codablecash {

CdbIntKey::CdbIntKey() : AbstractCdbKey(AbstractCdbKey::TYPE_INT) {
	this->value = 0;
}

CdbIntKey::~CdbIntKey() {

}

AbstractBtreeKey* CdbIntKey::clone() const noexcept {
}

int CdbIntKey::compareTo(const AbstractBtreeKey* key) const noexcept {
}

int CdbIntKey::binarySize() const {
	return sizeof(uint32_t) + sizeof(this->value);
}

void CdbIntKey::toBinary(ByteBuffer* out) const {
}

void CdbIntKey::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
