/*
 * TransactionOutputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionOutputs.h"
#include "bc_base/TransactionOutput.h"
#include "bc_base/BalanceUnit.h"

namespace codablecash {

TransactionOutputs::TransactionOutputs() {
	this->outputs = new ArrayList<TransactionOutput>;

}

TransactionOutputs::~TransactionOutputs() {
	this->outputs->deleteElements();
	delete this->outputs;
}

void TransactionOutputs::addOutput(const AbstractAddress* address, uint64_t amount) noexcept {
	TransactionOutput* output = new TransactionOutput(address, amount);
	this->outputs->addElement(output);
}

uint64_t TransactionOutputs::getTotalOutput() const noexcept {
	uint64_t total = 0;
	int maxLoop = this->outputs->size();
	for(int i = 0; i != maxLoop; ++i){
		TransactionOutput* out = this->outputs->get(i);
		total += out->getBalance()->getAmount();
	}

	return total;
}

} /* namespace codablecash */
