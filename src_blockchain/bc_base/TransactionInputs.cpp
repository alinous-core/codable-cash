/*
 * TransactionInputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionInputs.h"
#include "bc_base/TransactionInput.h"

namespace codablecash {

TransactionInputs::TransactionInputs() {
	this->inputs = new ArrayList<TransactionInput>();
}

TransactionInputs::~TransactionInputs() {
	this->inputs->deleteElements();
	delete this->inputs;
}

void TransactionInputs::addInput(const AbstractAddress* address, uint64_t amount) {
	TransactionInput* input = new TransactionInput(address, amount);
	this->inputs->addElement(input);
}

} /* namespace codablecash */
