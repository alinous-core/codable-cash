/*
 * InfinityKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/InfinityKey.h"
#include "btreekey/BTreeKeyFactory.h"

#include "base_io/ReverseByteBuffer.h"

namespace alinous {

InfinityKey::InfinityKey() : AbstractBtreeKey() {
}

InfinityKey::~InfinityKey() {
}

bool InfinityKey::isInfinity() {
	return true;
}

int alinous::InfinityKey::binarySize() {
	int size = sizeof(uint32_t);
	return size;
}

void alinous::InfinityKey::toBinary(ByteBuffer* out) {
	out->putInt(BTreeKeyFactory::INFINITY_KEY);
}

InfinityKey* InfinityKey::fromBinary(ByteBuffer* in) {
	return new InfinityKey();
}

int InfinityKey::compareTo(AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return 0;
	}
	return 1;
}

AbstractBtreeKey* InfinityKey::clone() const noexcept {
	return new InfinityKey();
}

} /* namespace alinous */

