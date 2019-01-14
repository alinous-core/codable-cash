/*
 * TransactionRecord.cpp
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#include "mempool/TransactionRecord.h"
#include "bc_base/Transaction.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

TransactionRecord::TransactionRecord(const AbstractTransaction* trx) {
	this->trx = trx->clone();
	this->trx->updateTransactionId();
}

TransactionRecord::~TransactionRecord() {
	delete this->trx;
}

int TransactionRecord::binarySize() const {
	return sizeof(char) + this->trx->binarySize();
}

void TransactionRecord::toBinary(ByteBuffer* out) const {
	int type = this->trx->getType();
	out->put(type);

	this->trx->toBinary(out);
}

AbstractTransaction* TransactionRecord::getTrx() const noexcept {
	return this->trx;
}

} /* namespace codablecash */
