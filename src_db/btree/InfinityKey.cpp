/*
 * InfinityKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/InfinityKey.h"
#include "btree/BTreeKeyFactory.h"

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


} /* namespace alinous */

