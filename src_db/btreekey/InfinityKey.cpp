/*
 * InfinityKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/InfinityKey.h"
#include "base_io/ReverseByteBuffer.h"

namespace alinous {

InfinityKey::InfinityKey() : AbstractBtreeKey() {
}

InfinityKey::~InfinityKey() {
}

bool InfinityKey::isInfinity() const {
	return true;
}

bool InfinityKey::isNull() const {
	return false;
}

int alinous::InfinityKey::binarySize() const {
	int size = sizeof(uint32_t);
	return size;
}

void InfinityKey::toBinary(ByteBuffer* out) const {
	out->putInt(BtreeKeyFactory::INFINITY_KEY);
}

InfinityKey* InfinityKey::fromBinary(ByteBuffer* in) {
	return new InfinityKey();
}

int InfinityKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return 0;
	}
	return 1;
}

AbstractBtreeKey* InfinityKey::clone() const noexcept {
	return new InfinityKey();
}

} /* namespace alinous */
