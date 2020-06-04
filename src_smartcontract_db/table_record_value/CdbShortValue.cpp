/*
 * CdbShortValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "table_record_value/CdbShortValue.h"

#include "base_io/ByteBuffer.h"

#include "table_record_key/CdbShortKey.h"

namespace codablecash {

CdbShortValue::CdbShortValue(const CdbShortValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_SHORT) {
	this->value = inst.value;
}

CdbShortValue::CdbShortValue() : AbstractCdbValue(AbstractCdbValue::TYPE_SHORT) {
	this->value = 0;
}

CdbShortValue::~CdbShortValue() {

}

int CdbShortValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int16_t);
	return total;
}

void CdbShortValue::toBinary(ByteBuffer* out) const {
	out->put(this->type);
	out->putShort(this->value);
}

void CdbShortValue::fromBinary(ByteBuffer* in) {
	this->value = in->getShort();
}

AbstractCdbKey* CdbShortValue::toKey() const noexcept {
	return new CdbShortKey(this->value);
}

} /* namespace codablecash */
