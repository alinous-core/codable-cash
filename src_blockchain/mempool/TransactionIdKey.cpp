/*
 * TransactionIdKey.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/TransactionIdKey.h"
#include "bc_base/TransactionId.h"

namespace codablecash {

TransactionIdKey::TransactionIdKey() {
	// TODO Auto-generated constructor stub

}

TransactionIdKey::~TransactionIdKey() {
	// TODO Auto-generated destructor stub
}

bool TransactionIdKey::isInfinity() const {
	return false;
}

int TransactionIdKey::compareTo(const AbstractBtreeKey* key) const noexcept {
}

AbstractBtreeKey* TransactionIdKey::clone() const noexcept {
}

int TransactionIdKey::binarySize() const {
}

void TransactionIdKey::toBinary(ByteBuffer* out) const {
}

} /* namespace codablecash */
