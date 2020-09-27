/*
 * FposValue.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/FposValue.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

FposValue::FposValue(uint64_t fpos) {
	this->fpos = fpos;
}

FposValue::~FposValue() {
}

int FposValue::binarySize() const {
	return sizeof(uint64_t);
}

void FposValue::toBinary(ByteBuffer* out) const {
	out->putLong(this->fpos);
}

FposValue* FposValue::fromBinary(ByteBuffer* in) {
	uint64_t fpos = in->getLong();
	return new FposValue(fpos);
}

IBlockObject* FposValue::copyData() const noexcept {
	return new FposValue(this->fpos);
}

} /* namespace codablecash */
