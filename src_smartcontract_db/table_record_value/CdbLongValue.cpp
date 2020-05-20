/*
 * CdbLongValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbLongValue.h"

namespace codablecash {

CdbLongValue::CdbLongValue(const CdbLongValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {
	this->value = inst.value;
}

CdbLongValue::CdbLongValue() : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {
	this->value = 0;
}

CdbLongValue::~CdbLongValue() {

}

int CdbLongValue::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

	const CdbLongValue* inst = dynamic_cast<const CdbLongValue*>(key);
	return this->value - inst->value;
}

AbstractBtreeKey* CdbLongValue::clone() const noexcept {
	return new CdbLongValue(*this);
}

int CdbLongValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int64_t);
	return total;
}

void CdbLongValue::toBinary(ByteBuffer* out) const {
}

void CdbLongValue::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
