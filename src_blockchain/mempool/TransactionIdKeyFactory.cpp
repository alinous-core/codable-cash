/*
 * TransactionIdKeyFactory.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/TransactionIdKeyFactory.h"
#include "mempool/TransactionIdKey.h"

namespace codablecash {

TransactionIdKeyFactory::TransactionIdKeyFactory() : BtreeKeyFactory() {
}

TransactionIdKeyFactory::~TransactionIdKeyFactory() {
}

AbstractBtreeKey* TransactionIdKeyFactory::fromBinary(uint32_t keyType,	ByteBuffer* in) const {
	if(keyType == TransactionIdKeyFactory::TRX_ID_KEY){
		return TransactionIdKey::fromBinary(in);
	}

	return BtreeKeyFactory::fromBinary(keyType, in);
}

BtreeKeyFactory* TransactionIdKeyFactory::copy() const noexcept {
	return new TransactionIdKeyFactory();
}


} /* namespace codablecash */
