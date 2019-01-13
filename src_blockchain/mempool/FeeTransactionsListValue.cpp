/*
 * FeeTransactionsListValue.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/FeeTransactionsListValue.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

FeeTransactionsListValue::FeeTransactionsListValue() : list(8), IBlockObject() {
}

FeeTransactionsListValue::FeeTransactionsListValue(uint64_t value) : list(8), IBlockObject() {
	this->list.addElement(value);
}

FeeTransactionsListValue::~FeeTransactionsListValue() {
}

int FeeTransactionsListValue::binarySize() const {
	int total = sizeof(uint32_t);
	total += sizeof(uint64_t) * this->list.size();

	return total;
}

void FeeTransactionsListValue::toBinary(ByteBuffer* out) const {
	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = this->list.get(i);
		out->putLong(fpos);
	}
}

FeeTransactionsListValue* FeeTransactionsListValue::fromBinary(ByteBuffer* in) {
	FeeTransactionsListValue* value = new FeeTransactionsListValue();

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = in->getLong();
		value->list.addElement(fpos);
	}

	return value;
}

void FeeTransactionsListValue::join(const FeeTransactionsListValue* value) noexcept {
	// FIXME
}

} /* namespace codablecash */
