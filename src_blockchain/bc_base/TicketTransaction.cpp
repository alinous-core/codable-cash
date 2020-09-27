/*
 * TicketTransaction.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "TicketTransaction.h"

#include "flash_pow/Nonce.h"
#include "bc_base/TransactionId.h"
#include "bc_base/BalanceUnit.h"

#include "base/StackRelease.h"
#include "base_io/ByteBuffer.h"

#include "../../src/crypto/Sha256.h"
namespace codablecash {

TicketTransaction::TicketTransaction(uint64_t fheight) : AbstractTransaction(AbstractTransaction::TYPE_TICKET) {
	this->fheight = fheight;
	this->nonce = nullptr;
	this->fee = nullptr;
	this->trxId = nullptr;
}

TicketTransaction::~TicketTransaction() {
	delete this->nonce;
	delete this->fee;
	delete this->trxId;
}



int TicketTransaction::binarySize() const {
	int total = sizeof(char);

	total += sizeof(this->fheight);
	total += this->nonce->binarySize();
	total += this->fee->binarySize();

	return total;
}

void TicketTransaction::toBinary(ByteBuffer* out) const {
	out->put(AbstractTransaction::TYPE_TICKET);

	out->putLong(this->fheight);
	this->nonce->toBinary(out);
	this->fee->toBinary(out);
}

AbstractTransaction* TicketTransaction::clone() const {
	TicketTransaction* inst = new TicketTransaction(this->fheight);
	inst->nonce = new Nonce(*this->nonce);
	inst->fee = new BalanceUnit(*this->fee);

	return inst;
}

void TicketTransaction::updateTransactionId() {
	if(this->trxId != nullptr){
		delete this->trxId, this->trxId = nullptr;
	}

	int size = binarySize();

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	toBinary(buff);

	ByteBuffer* sha = Sha256::sha256((const char*)buff->array(), size, true); __STP(sha);

	this->trxId = new TransactionId((const char*)sha->array(), sha->capacity());
}

const TransactionId* TicketTransaction::getTransactionId() const noexcept {
	return this->trxId;
}

const BalanceUnit* TicketTransaction::getFee() const noexcept {
	return this->fee;
}

void TicketTransaction::setNonce(const Nonce* nonce) noexcept {
	this->nonce = new Nonce(*nonce);
}

void TicketTransaction::setFee(const BalanceUnit* fee) noexcept {
	this->fee = new BalanceUnit(*fee);
}

IBlockObject* TicketTransaction::copyData() const noexcept {
	// FIXME copyData()
	return nullptr;
}

} /* namespace codablecash */
