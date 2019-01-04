/*
 * BalanceUnit.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/BalanceUnit.h"
#include "base_io/ByteBuffer.h"

namespace codablecash {

BalanceUnit::BalanceUnit(uint64_t amount) {
	this->amount = amount;
}

BalanceUnit::~BalanceUnit() {
}

uint64_t BalanceUnit::getAmount() const noexcept {
	return this->amount;
}

int BalanceUnit::binarySize() const {
	return sizeof(uint64_t);
}

void BalanceUnit::toBinary(ByteBuffer* out) const {
	out->putLong(this->amount);
}

} /* namespace codablecash */
