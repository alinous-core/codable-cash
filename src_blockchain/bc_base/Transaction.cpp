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

namespace codablecash {

Transaction::Transaction() : AbstractTransaction(AbstractTransaction::TYPE_SEND_BALANCE) {
	this->inputs = new TransactionInputs();
	this->outputs = new TransactionOutputs();
	this->fee = new BalanceUnit(0L);
}

Transaction::~Transaction() {
	delete this->inputs;
	delete this->outputs;
	delete this->fee;
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

	return total;
}

void Transaction::toBinary(ByteBuffer* out) const {
	this->inputs->toBinary(out);
	this->outputs->toBinary(out);
	this->fee->toBinary(out);
}

Transaction* Transaction::fromBinary(ByteBuffer* in) {
	Transaction* trx = new Transaction();

	trx->inputs->importBinary(in);
	trx->outputs->importBinary(in);
	trx->fee->importBinary(in);

	return trx;
}

} /* namespace codablecash */

