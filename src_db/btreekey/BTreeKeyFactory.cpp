/*
 * BTreeKeyFactory.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/BTreeKeyFactory.h"
#include "btreekey/InfinityKey.h"

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
		break;
	default:
		break;
	}


}


} /* namespace alinous */

