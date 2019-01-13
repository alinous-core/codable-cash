/*
 * TransactionOutputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionOutputs.h"
#include "bc_base/TransactionOutput.h"
#include "bc_base/BalanceUnit.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

TransactionOutputs::TransactionOutputs(const TransactionOutputs& inst) {
	this->outputs = new ArrayList<TransactionOutput>;

	int maxLoop = inst.outputs->size();
	for(int i = 0; i != maxLoop; ++i){
		const TransactionOutput* out = inst.outputs->get(i);
		this->outputs->addElement(new TransactionOutput(*out));
	}
}

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

int TransactionOutputs::binarySize() const {
	int total = sizeof(int32_t);

	int maxLoop = this->outputs->size();
	for(int i = 0; i != maxLoop; ++i){
		TransactionOutput* output = this->outputs->get(i);
		total += output->binarySize();
	}

	return total;
}

void TransactionOutputs::toBinary(ByteBuffer* out) const {
	int maxLoop = this->outputs->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		TransactionOutput* output = this->outputs->get(i);
		output->toBinary(out);
	}
}

void codablecash::TransactionOutputs::importBinary(ByteBuffer* in) {
	int maxLoop =in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		TransactionOutput* output = TransactionOutput::fromBinary(in);
		this->outputs->addElement(output);
	}
}

} /* namespace codablecash */
