/*
 * CdbLongValue.cpp
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#include "schema_table/table_record_value/CdbLongValue.h"

#include "base_io/ByteBuffer.h"

#include "schema_table/table_record_key/CdbLongKey.h"

namespace codablecash {

CdbLongValue::CdbLongValue(const CdbLongValue& inst) : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {
	this->value = inst.value;
}

CdbLongValue::CdbLongValue(int64_t value) : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {
	this->value = value;
}

CdbLongValue::CdbLongValue() : AbstractCdbValue(AbstractCdbValue::TYPE_LONG) {
	this->value = 0;
}

CdbLongValue::~CdbLongValue() {

}

int CdbLongValue::binarySize() const {
	int total = sizeof(int8_t);
	total += sizeof(int64_t);
	return total;
}

void CdbLongValue::toBinary(ByteBuffer* out) const {
	out->put(this->type);
	out->putLong(this->value);
}

void CdbLongValue::fromBinary(ByteBuffer* in) {
	this->value = in->getLong();
}

AbstractCdbKey* CdbLongValue::toKey() const noexcept {
	return new CdbLongKey(this->value);
}

AbstractCdbValue* CdbLongValue::copy() const noexcept {
	return new CdbLongValue(*this);
}

} /* namespace codablecash */
