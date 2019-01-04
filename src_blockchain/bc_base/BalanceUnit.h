/*
 * BalanceUnit.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_BALANCEUNIT_H_
#define BC_BASE_BALANCEUNIT_H_

#include <inttypes.h>

namespace codablecash {

class BalanceUnit {
public:
	BalanceUnit(uint64_t amount);
	virtual ~BalanceUnit();

	uint64_t getAmount() const noexcept;
	void setAmount(uint64_t amount) noexcept{this->amount = amount;}
private:
	uint64_t amount;
};

} /* namespace codablecash */

#endif /* BC_BASE_BALANCEUNIT_H_ */
