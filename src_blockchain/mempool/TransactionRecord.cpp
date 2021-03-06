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

TransactionRecord::TransactionRecord() {
	this->trx = nullptr;
}

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
	this->trx->toBinary(out);
}

TransactionRecord* TransactionRecord::fromBinary(ByteBuffer* in) {
	TransactionRecord* rec = new TransactionRecord();
	rec->trx = AbstractTransaction::fromBinary(in);

	return rec;
}

const AbstractTransaction* TransactionRecord::getTrx() const noexcept {
	return this->trx;
}

IBlockObject* TransactionRecord::copyData() const noexcept {
	return new TransactionRecord(this->trx);
}

} /* namespace codablecash */
