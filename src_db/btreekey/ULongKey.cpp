/*
 * LongKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/ULongKey.h"
#include "btreekey/BTreeKeyFactory.h"

#include "base_io/ReverseByteBuffer.h"

namespace alinous {

ULongKey::ULongKey(uint64_t value) {
	this->value = value;
}

ULongKey::~ULongKey() {
}

int ULongKey::binarySize() {
	int size = sizeof(uint32_t);
	size += sizeof(this->value);
	return size;
}

void ULongKey::toBinary(ByteBuffer* out) {
	out->putInt(BTreeKeyFactory::ULONG_KEY);
	out->putLong(this->value);
}

ULongKey* ULongKey::fromBinary(ByteBuffer* in) {
	uint64_t value = in->getLong();
	return new ULongKey(value);
}


} /* namespace alinous */

