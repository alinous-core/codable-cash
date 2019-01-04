/*
 * TransactionOutput.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONOUTPUT_H_
#define BC_BASE_TRANSACTIONOUTPUT_H_

#include <inttypes.h>

namespace codablecash {

class BalanceUnit;
class AbstractAddress;

class TransactionOutput {
public:
	TransactionOutput(const AbstractAddress* address, uint64_t amount);
	virtual ~TransactionOutput();

	BalanceUnit* getBalance() const noexcept;
private:
	BalanceUnit* balance;
	AbstractAddress* address;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONOUTPUT_H_ */
