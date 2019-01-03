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

void Transaction::addInput(const AbstractAddress* address, uint64_t amount) {
	this->inputs->addInput(address, amount);
}

void Transaction::addOutput(const AbstractAddress* address, uint64_t amount) {
	this->outputs->addOutput(address, amount);
}


} /* namespace codablecash */

