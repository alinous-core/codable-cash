/*
 * TransactionInputs.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONINPUTS_H_
#define BC_BASE_TRANSACTIONINPUTS_H_

#include "base/ArrayList.h"

namespace codablecash {
using namespace alinous;

class TransactionInput;

class TransactionInputs {
public:
	TransactionInputs();
	virtual ~TransactionInputs();

private:
	ArrayList<TransactionInput>* inputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONINPUTS_H_ */
