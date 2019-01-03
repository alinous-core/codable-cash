/*
 * BalanceUnit.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/BalanceUnit.h"

namespace codablecash {

BalanceUnit::BalanceUnit() {
	this->amount = 0;
}

BalanceUnit::~BalanceUnit() {
}

uint64_t BalanceUnit::getAmount() const noexcept {
	return this->amount;
}

} /* namespace codablecash */
