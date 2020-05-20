/*
 * CdbByteValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbByteValue.h"

namespace codablecash {

CdbByteValue::CdbByteValue(const CdbByteValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_BYTE) {
	this->value = inst.value;
}

CdbByteValue::CdbByteValue() : AbstractCdbValue(AbstractCdbValue::TYPE_BYTE) {
	this->value = 0;
}

CdbByteValue::~CdbByteValue() {

}

int CdbByteValue::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
}

AbstractBtreeKey* CdbByteValue::clone() const noexcept {
	return new CdbByteValue(*this);
}

int CdbByteValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int8_t);
	return total;
}

void CdbByteValue::toBinary(ByteBuffer* out) const {
}

void CdbByteValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
