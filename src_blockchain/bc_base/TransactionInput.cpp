/*
 * TransactionInput.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionInput.h"
#include "bc_base/BalanceUnit.h"
#include "AbstractAddress.h"

namespace codablecash {

TransactionInput::TransactionInput(const AbstractAddress* address, uint64_t amount) {
	this->address = address->clone();
	this->balance = new BalanceUnit(amount);

}

TransactionInput::~TransactionInput() {
	delete this->address;
	delete this->balance;
}



} /* namespace codablecash */
