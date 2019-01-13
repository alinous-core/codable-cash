/*
 * TransactionIdKeyFactory.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/TransactionIdKeyFactory.h"

namespace codablecash {

TransactionIdKeyFactory::TransactionIdKeyFactory() : BtreeKeyFactory() {
}

TransactionIdKeyFactory::~TransactionIdKeyFactory() {
}

AbstractBtreeKey* TransactionIdKeyFactory::fromBinary(uint32_t keyType,	ByteBuffer* in) const {
	if(keyType == TransactionIdKeyFactory::TRX_ID_KEY){
		// FIXME
	}

	return BtreeKeyFactory::fromBinary(keyType, in);
}

} /* namespace codablecash */
