/*
 * TransactionOutputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionOutputs.h"
#include "bc_base/TransactionOutput.h"

namespace codablecash {

TransactionOutputs::TransactionOutputs() {
	this->outputs = new ArrayList<TransactionOutput>;

}

TransactionOutputs::~TransactionOutputs() {
	this->outputs->deleteElements();
	delete this->outputs;
}

void TransactionOutputs::addOutput(const AbstractAddress* address, uint64_t amount) {
	TransactionOutput* output = new TransactionOutput(address, amount);
	this->outputs->addElement(output);
}

} /* namespace codablecash */
