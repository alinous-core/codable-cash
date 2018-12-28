/*
 * BTreeKeyFactory.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/BTreeKeyFactory.h"
#include "btreekey/InfinityKey.h"
#include "btreekey/ULongKey.h"
#include "btreekey/exceptions.h"

namespace alinous {

BTreeKeyFactory::BTreeKeyFactory() {
}

BTreeKeyFactory::~BTreeKeyFactory() {
}

AbstractBtreeKey* BTreeKeyFactory::fromBinary(uint32_t keyType, ByteBuffer* in) {
	switch(keyType){
	case BTreeKeyFactory::INFINITY_KEY:
		return InfinityKey::fromBinary(in);
	case BTreeKeyFactory::ULONG_KEY:
		return ULongKey::fromBinary(in);
	default:
		break;
	}

	throw new KeyFormatException(__FILE__, __LINE__);
}


} /* namespace alinous */

