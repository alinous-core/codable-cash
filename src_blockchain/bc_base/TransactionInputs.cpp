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

void TransactionInputs::addInput(const AbstractAddress* address, uint64_t amount) noexcept {
	TransactionInput* input = new TransactionInput(address, amount);
	this->inputs->addElement(input);
}

uint64_t TransactionInputs::getTotalInput() const noexcept {
	uint64_t total = 0;

	int maxLoop = this->inputs->size();
	for(int i = 0; i != maxLoop; ++i){
		TransactionInput* input = this->inputs->get(i);
		total += input->getBalanceAmount();

	}

	return total;
}


} /* namespace codablecash */

