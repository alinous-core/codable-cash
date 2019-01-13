/*
 * LongKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/ULongKey.h"
#include "base_io/ReverseByteBuffer.h"

namespace alinous {

ULongKey::ULongKey(uint64_t value) {
	this->value = value;
}

ULongKey::~ULongKey() {
}

int ULongKey::binarySize() const {
	int size = sizeof(uint32_t);
	size += sizeof(this->value);
	return size;
}

void ULongKey::toBinary(ByteBuffer* out) const {
	out->putInt(BtreeKeyFactory::ULONG_KEY);
	out->putLong(this->value);
}

ULongKey* ULongKey::fromBinary(ByteBuffer* in) {
	uint64_t value = in->getLong();
	return new ULongKey(value);
}

int ULongKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

	const ULongKey* ulkey = dynamic_cast<const ULongKey*>(key);

	return this->value - ulkey->value;
}

AbstractBtreeKey* ULongKey::clone() const noexcept {
	return new ULongKey(this->value);
}

} /* namespace alinous */

