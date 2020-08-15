/*
 * FeeIndexKey.cpp
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#include "mempool_idx/FeeIndexKey.h"
#include "mempool_idx/FeeIndexKeyFactory.h"

#include "base_io/ByteBuffer.h"

namespace codablecash {

FeeIndexKey::FeeIndexKey(uint64_t value) {
	this->value = value;
	this->fpos = 0;
}

FeeIndexKey::FeeIndexKey(uint64_t value, uint64_t fpos) {
	this->value = value;
	this->fpos = fpos;
}

FeeIndexKey::~FeeIndexKey() {
}

int FeeIndexKey::binarySize() const {
	int size = sizeof(uint32_t);
	size += sizeof(this->value) + sizeof(this->fpos);
	return size;
}

void FeeIndexKey::toBinary(ByteBuffer* out) const {
	out->putInt(FeeIndexKeyFactory::FEE_INDEX_KEY);
	out->putLong(this->value);
	out->putLong(this->fpos);
}

FeeIndexKey* FeeIndexKey::fromBinary(ByteBuffer* in) {
	uint64_t value = in->getLong();
	uint64_t fpos = in->getLong();

	return new FeeIndexKey(value, fpos);
}

int FeeIndexKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}
	else if(key->isNull()){
		return 1;
	}

	const FeeIndexKey* ulkey = dynamic_cast<const FeeIndexKey*>(key);

	return this->value - ulkey->value;
}

AbstractBtreeKey* FeeIndexKey::clone() const noexcept {
	return new FeeIndexKey(this->value, this->fpos);
}

} /* namespace codablecash */
