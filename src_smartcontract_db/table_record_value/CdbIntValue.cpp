/*
 * CdbIntValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbIntValue.h"

#include "base_io/ByteBuffer.h"

#include "table_record_key/CdbIntKey.h"

namespace codablecash {

CdbIntValue::CdbIntValue(const CdbIntValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {
	this->value = inst.value;
}

CdbIntValue::CdbIntValue() : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {
	this->value = 0;
}

CdbIntValue::CdbIntValue(int32_t value) : AbstractCdbValue(AbstractCdbValue::TYPE_INT) {
	this->value = value;
}

CdbIntValue::~CdbIntValue() {

}

int CdbIntValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int32_t);
	return total;
}

void CdbIntValue::toBinary(ByteBuffer* out) const {
	out->put(this->type);
	out->putInt(this->value);
}

void CdbIntValue::fromBinary(ByteBuffer* in) {
	this->value = in->getInt();
}

AbstractCdbKey* CdbIntValue::toKey() const noexcept {
	return new CdbIntKey(this->value);
}

} /* namespace codablecash */
