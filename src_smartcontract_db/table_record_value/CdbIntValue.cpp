/*
 * CdbIntValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbIntValue.h"

namespace codablecash {

CdbIntValue::CdbIntValue(const CdbIntValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {
	this->value = inst.value;
}

CdbIntValue::CdbIntValue() : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {
	this->value = 0;
}

CdbIntValue::~CdbIntValue() {

}

int CdbIntValue::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
}

AbstractBtreeKey* CdbIntValue::clone() const noexcept {
	return new CdbIntValue(*this);
}

int CdbIntValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int32_t);
	return total;
}

void CdbIntValue::toBinary(ByteBuffer* out) const {
}

void CdbIntValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
