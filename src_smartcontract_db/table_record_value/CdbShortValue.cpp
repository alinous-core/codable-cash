/*
 * CdbShortValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbShortValue.h"

namespace codablecash {

CdbShortValue::CdbShortValue(const CdbShortValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_SHORT) {
	this->value = inst.value;
}

CdbShortValue::CdbShortValue() : AbstractCdbValue(AbstractCdbValue::TYPE_SHORT) {
	this->value = 0;
}

CdbShortValue::~CdbShortValue() {

}

int CdbShortValue::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

}

AbstractBtreeKey* CdbShortValue::clone() const noexcept {
	return new CdbShortValue(*this);
}

int CdbShortValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int16_t);
	return total;
}

void CdbShortValue::toBinary(ByteBuffer* out) const {
}

void CdbShortValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
