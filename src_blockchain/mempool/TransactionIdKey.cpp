/*
 * TransactionIdKey.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/TransactionIdKey.h"
#include "bc_base/TransactionId.h"

namespace codablecash {

TransactionIdKey::TransactionIdKey(const TransactionId trxId) : AbstractBtreeKey() {
	// TODO Auto-generated constructor stub

}

TransactionIdKey::~TransactionIdKey() {
	delete this->trxId;
}

bool TransactionIdKey::isInfinity() const {
	return false;
}

int TransactionIdKey::compareTo(const AbstractBtreeKey* key) const noexcept {
	if(key->isInfinity()){
		return -1;
	}

	const TransactionId* id2 = dynamic_cast<const TransactionId*>(key);



}

AbstractBtreeKey* TransactionIdKey::clone() const noexcept {
}

int TransactionIdKey::binarySize() const {
}

void TransactionIdKey::toBinary(ByteBuffer* out) const {
}

} /* namespace codablecash */
