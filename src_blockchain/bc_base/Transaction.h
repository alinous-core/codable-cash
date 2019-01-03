/*
 * Transaction.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTION_H_
#define BC_BASE_TRANSACTION_H_

#include <inttypes.h>

#include "bc_base/AbstractTransaction.h"

namespace codablecash {

class TransactionInputs;
class TransactionOutputs;
class BalanceUnit;
class AbstractAddress;

class Transaction : public AbstractTransaction {
public:
	Transaction();
	virtual ~Transaction();

	void addInput(const AbstractAddress* address, uint64_t amount);
	void addOutput(const AbstractAddress* address, uint64_t amount);

private:
	// body part
	TransactionInputs* inputs;
	TransactionOutputs* outputs;
	BalanceUnit* fee;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTION_H_ */
