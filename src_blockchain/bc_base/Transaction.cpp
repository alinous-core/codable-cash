/*
 * Transaction.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/Transaction.h"
#include "bc_base/TransactionInputs.h"

namespace codablecash {

Transaction::Transaction() : AbstractTransaction(AbstractTransaction::TYPE_SEND_BALANCE) {
	this->inputs = new TransactionInputs();
}

Transaction::~Transaction() {
	delete this->inputs;
}

} /* namespace codablecash */
