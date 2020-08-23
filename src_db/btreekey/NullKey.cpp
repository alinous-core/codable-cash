/*
 * NullKey.cpp
 *
 *  Created on: 2020/08/15
 *      Author: iizuka
 */

#include "btreekey/NullKey.h"
#include "btreekey/BtreeKeyFactory.h"

#include "base_io/ByteBuffer.h"

#include "btree/AbstractBtreeKey.h"

namespace alinous {

NullKey::NullKey() : AbstractBtreeKey() {

}

NullKey::~NullKey() {

}

bool NullKey::isInfinity() const {
	return false;
}

bool NullKey::isNull() const {
	return true;
}

int NullKey::binarySize() const {
	int size = sizeof(uint32_t);
	return size;
}

void NullKey::toBinary(ByteBuffer* out) const {
	out->putInt(BtreeKeyFactory::NULL_KEY);
}

NullKey* NullKey::fromBinary(ByteBuffer* in) {
	return new NullKey();
}

int NullKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isNull()){
		return 0;
	}
	return -1;
}

AbstractBtreeKey* NullKey::clone() const noexcept {
	return new NullKey();
}

} /* namespace alinous */
