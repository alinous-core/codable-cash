/*
 * Transaction.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/Transaction.h"
#include "bc_base/TransactionInputs.h"
#include "bc_base/TransactionOutputs.h"
#include "bc_base/BalanceUnit.h"
#include "bc_base/AbstractAddress.h"
#include "bc_base/TransactionId.h"

#include "base_io/ByteBuffer.h"
#include "osenv/funcs.h"
#include "base/StackRelease.h"

#include "crypto/Sha256.h"

namespace codablecash {

Transaction::Transaction(const Transaction& inst) : AbstractTransaction(inst) {
	this->inputs = new TransactionInputs(*inst.inputs);
	this->outputs = new TransactionOutputs(*inst.outputs);
	this->fee = new BalanceUnit(inst.fee->getAmount());
	this->timelong = inst.timelong;

	this->trxId = nullptr;
	if(inst.trxId != nullptr){
		this->trxId = new TransactionId(*inst.trxId);
	}
}

Transaction::Transaction() : AbstractTransaction(AbstractTransaction::TYPE_SEND_BALANCE) {
	this->inputs = new TransactionInputs();
	this->outputs = new TransactionOutputs();
	this->fee = new BalanceUnit(0L);
	this->timelong = Os::getTimestampLong();
	this->trxId = nullptr;
}

Transaction::~Transaction() {
	delete this->inputs;
	delete this->outputs;
	delete this->fee;
	if(this->trxId != nullptr){
		delete this->trxId;
	}
}

void Transaction::addInput(const AbstractAddress* address, uint64_t amount) noexcept {
	this->inputs->addInput(address, amount);
}

void Transaction::addOutput(const AbstractAddress* address, uint64_t amount) noexcept {
	this->outputs->addOutput(address, amount);
}

uint64_t Transaction::getTotalInput() const noexcept {
	return this->inputs->getTotalInput();
}

uint64_t Transaction::getTotalOutput() const noexcept {
	return this->outputs->getTotalOutput() + this->fee->getAmount();
}

void Transaction::setFee(uint64_t amount) noexcept {
	this->fee->setAmount(amount);
}

int Transaction::binarySize() const {
	int total = this->inputs->binarySize();
	total += this->outputs->binarySize();
	total += this->fee->binarySize();

	total += sizeof(uint64_t);

	return total;
}

void Transaction::toBinary(ByteBuffer* out) const {
	this->inputs->toBinary(out);
	this->outputs->toBinary(out);
	this->fee->toBinary(out);
	out->putLong(this->timelong);
}

Transaction* Transaction::fromBinary(ByteBuffer* in) {
	Transaction* trx = new Transaction();

	trx->inputs->importBinary(in);
	trx->outputs->importBinary(in);
	trx->fee->importBinary(in);
	trx->timelong = in->getLong();

	return trx;
}

void Transaction::updateTransactionId() {
	if(this->trxId != nullptr){
		delete this->trxId, this->trxId = nullptr;
	}

	int size = this->inputs->binarySize();
	size += this->outputs->binarySize();
	size += this->fee->binarySize();
	size += sizeof(uint64_t);

	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true);
	StackRelease<ByteBuffer> __st_buff(buff);

	this->inputs->toBinary(buff);
	this->outputs->toBinary(buff);
	this->fee->toBinary(buff);
	buff->putLong(this->timelong);

	ByteBuffer* sha = Sha256::sha256((const char*)buff->array(), size, true);
	StackRelease<ByteBuffer> __st_sha(sha);

	this->trxId = new TransactionId((const char*)sha->array(), sha->capacity());
}

const TransactionId* Transaction::getTransactionId() const noexcept {
	return this->trxId;
}

AbstractTransaction* Transaction::clone() const {
	AbstractTransaction* trx = new Transaction(*this);
	return trx;
}

const BalanceUnit* Transaction::getFee() const noexcept {
	return this->fee;
}

} /* namespace codablecash */
