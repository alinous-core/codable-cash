/*
 * TransactionIdKey.cpp
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#include "mempool/TransactionIdKey.h"
#include "bc_base/TransactionId.h"
#include "mempool/TransactionIdKeyFactory.h"

#include "base_io/ByteBuffer.h"
#include "osenv/funcs.h"

namespace codablecash {

TransactionIdKey::TransactionIdKey() {
	this->trxId = nullptr;
}

TransactionIdKey::TransactionIdKey(const TransactionId* trxId) : AbstractBtreeKey() {
	this->trxId = new TransactionId(*trxId);
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

	const TransactionIdKey* key2 = dynamic_cast<const TransactionIdKey*>(key);

	int size = this->trxId->size();
/*	int size2 = key2->trxId->size();
	if(size != size2){
		return size - size2;
	}*/

	return Mem::memcmp(this->trxId->toArray(), key2->trxId->toArray(), size);
}

AbstractBtreeKey* TransactionIdKey::clone() const noexcept {
	TransactionIdKey* key = new TransactionIdKey(this->trxId);
	return key;
}

int TransactionIdKey::binarySize() const {
	int total = sizeof(TransactionIdKeyFactory::TRX_ID_KEY);
	total += this->trxId->binarySize();

	return total;
}

void TransactionIdKey::toBinary(ByteBuffer* out) const {
	out->putInt(TransactionIdKeyFactory::TRX_ID_KEY);
	this->trxId->toBinary(out);
}

TransactionIdKey* TransactionIdKey::fromBinary(ByteBuffer* in) {
	TransactionIdKey* key = new TransactionIdKey();
	key->trxId = TransactionId::fromBinary(in);

	return key;
}

} /* namespace codablecash */


