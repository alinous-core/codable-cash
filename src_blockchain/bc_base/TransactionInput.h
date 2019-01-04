/*
 * TransactionInput.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONINPUT_H_
#define BC_BASE_TRANSACTIONINPUT_H_

#include <inttypes.h>

namespace codablecash {

class BalanceUnit;
class AbstractAddress;

class TransactionInput {
public:
	TransactionInput(const AbstractAddress* address, uint64_t amount);
	virtual ~TransactionInput();

	uint64_t getBalanceAmount() const noexcept;

private:
	BalanceUnit* balance;
	AbstractAddress* address;

};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONINPUT_H_ */
