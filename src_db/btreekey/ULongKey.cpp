/*
 * LongKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/ULongKey.h"
#include "btree/BTreeKeyFactory.h"

#include "base_io/ReverseByteBuffer.h"

namespace alinous {

ULongKey::ULongKey(uint64_t value) {
	this->value = value;
}

ULongKey::~ULongKey() {
}

int ULongKey::binarySize() {
	int size = sizeof(char);
	size += sizeof(this->value);
	return size;
}

void ULongKey::toBinary(ByteBuffer* out) {
	out->put(BTreeKeyFactory::ULONG_KEY);
	out->putLong(this->value);

}

} /* namespace alinous */
