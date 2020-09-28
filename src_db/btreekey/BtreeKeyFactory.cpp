/*
 * BTreeKeyFactory.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/NullKey.h"
#include "btreekey/InfinityKey.h"
#include "btreekey/ULongKey.h"
#include "btreekey/exceptions.h"

namespace alinous {

BtreeKeyFactory::BtreeKeyFactory() {
}

BtreeKeyFactory::~BtreeKeyFactory() {
}

AbstractBtreeKey* BtreeKeyFactory::fromBinary(uint32_t keyType, ByteBuffer* in) const {
	switch(keyType){
	case BtreeKeyFactory::NULL_KEY:
		return NullKey::fromBinary(in);
	case BtreeKeyFactory::INFINITY_KEY:
		return InfinityKey::fromBinary(in);
	case BtreeKeyFactory::ULONG_KEY:
		return ULongKey::fromBinary(in);
	default:
		break;
	}

	throw new KeyFormatException(__FILE__, __LINE__);
}

BtreeKeyFactory* BtreeKeyFactory::copy() const noexcept {
	return new BtreeKeyFactory();
}

} /* namespace alinous */
