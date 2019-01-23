/*
 * FeeIndexKeyFactory.cpp
 *
 *  Created on: 2019/01/14
 *      Author: iizuka
 */

#include "mempool_idx/FeeIndexKeyFactory.h"
#include "mempool_idx/FeeIndexKey.h"

namespace codablecash {

FeeIndexKeyFactory::FeeIndexKeyFactory() {
}

FeeIndexKeyFactory::~FeeIndexKeyFactory() {
}

AbstractBtreeKey* FeeIndexKeyFactory::fromBinary(uint32_t keyType, ByteBuffer* in) const {
	if(keyType == FeeIndexKeyFactory::FEE_INDEX_KEY){
		return FeeIndexKey::fromBinary(in);
	}

	return BtreeKeyFactory::fromBinary(keyType, in);
}

} /* namespace codablecash */
