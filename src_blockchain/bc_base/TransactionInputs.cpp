/*
 * TransactionInputs.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/TransactionInputs.h"
#include "bc_base/TransactionInput.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

codablecash::TransactionInputs::TransactionInputs(const TransactionInputs& inst) {
	this->inputs = new ArrayList<TransactionInput>();

	int maxLoop = inst.inputs->size();
	for(int i = 0; i != maxLoop; ++i){
		const TransactionInput* in = inst.inputs->get(i);

		this->inputs->addElement(new TransactionInput(*in));
	}
}

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

int TransactionInputs::binarySize() const {
	int total = sizeof(int32_t);

	int maxLoop = this->inputs->size();
	for(int i = 0; i != maxLoop; ++i){
		TransactionInput* input = this->inputs->get(i);
		total += input->binarySize();
	}

	return total;
}

void TransactionInputs::toBinary(ByteBuffer* out) const {
	int maxLoop = this->inputs->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		TransactionInput* input = this->inputs->get(i);
		input->toBinary(out);
	}
}

void TransactionInputs::importBinary(ByteBuffer* in) {
	int maxLoop =in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		TransactionInput* input = TransactionInput::fromBinary(in);
		this->inputs->addElement(input);
	}
}

} /* namespace codablecash */
