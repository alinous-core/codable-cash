/*
 * TransactionInput.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionInput.h"
#include "bc_base/BalanceUnit.h"
#include "BlockchainAddress.h"


namespace codablecash {

TransactionInput::TransactionInput(const TransactionInput& inst) {
	this->address = inst.address->clone();
	this->balance = new BalanceUnit(inst.balance->getAmount());
}


TransactionInput::TransactionInput() {
	this->address = nullptr;
	this->balance = nullptr;
}

TransactionInput::TransactionInput(const AbstractAddress* address, uint64_t amount) {
	this->address = address->clone();
	this->balance = new BalanceUnit(amount);

}

TransactionInput::~TransactionInput() {
	delete this->address;
	delete this->balance;
}

uint64_t TransactionInput::getBalanceAmount() const noexcept {
	return this->balance->getAmount();
}

int TransactionInput::binarySize() const {
	int total = this->address->binarySize();
	total += this->balance->binarySize();

	return total;
}

void TransactionInput::toBinary(ByteBuffer* out) const {
	this->address->toBinary(out);
	this->balance->toBinary(out);
}

TransactionInput* TransactionInput::fromBinary(ByteBuffer* in) {
	TransactionInput* input = new TransactionInput();

	input->address = BlockchainAddress::fromBinary(in);
	input->balance = new BalanceUnit(0);
	input->balance->importBinary(in);

	return input;
}

IBlockObject* TransactionInput::copyData() const noexcept {
	return new TransactionInput(*this);
}

} /* namespace codablecash */
