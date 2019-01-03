/*
 * Transaction.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTION_H_
#define BC_BASE_TRANSACTION_H_

#include "bc_base/AbstractTransaction.h"

namespace codablecash {

class TransactionInputs;

class Transaction : public AbstractTransaction {
public:
	Transaction();
	virtual ~Transaction();

private:
	TransactionInputs* inputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTION_H_ */
