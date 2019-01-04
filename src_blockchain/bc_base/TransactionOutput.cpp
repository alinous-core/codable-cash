/*
 * TransactionOutput.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionOutput.h"
#include "bc_base/BalanceUnit.h"
#include "AbstractAddress.h"

namespace codablecash {

TransactionOutput::TransactionOutput(const AbstractAddress* address, uint64_t amount) {
	this->address = address->clone();
	this->balance = new BalanceUnit(amount);
}

TransactionOutput::~TransactionOutput() {
	delete this->address;
	delete this->balance;
}

BalanceUnit* TransactionOutput::getBalance() const noexcept {
	return this->balance;
}

int TransactionOutput::binarySize() const {
	int total = this->address->binarySize();
	total += this->balance->binarySize();

	return total;
}

void TransactionOutput::toBinary(ByteBuffer* out) const {
	this->address->toBinary(out);
	this->balance->toBinary(out);
}

} /* namespace codablecash */


