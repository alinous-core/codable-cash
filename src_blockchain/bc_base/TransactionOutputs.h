/*
 * TransactionOutputs.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONOUTPUTS_H_
#define BC_BASE_TRANSACTIONOUTPUTS_H_

#include "base/ArrayList.h"

namespace codablecash {
using namespace alinous;

class TransactionOutput;

class TransactionOutputs {
public:
	TransactionOutputs();
	virtual ~TransactionOutputs();

private:
	ArrayList<TransactionOutput>* outputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONOUTPUTS_H_ */
