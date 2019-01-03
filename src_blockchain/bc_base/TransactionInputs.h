/*
 * TransactionInputs.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONINPUTS_H_
#define BC_BASE_TRANSACTIONINPUTS_H_

#include <inttypes.h>

#include "base/ArrayList.h"

namespace codablecash {
using namespace alinous;

class TransactionInput;
class AbstractAddress;

class TransactionInputs {
public:
	TransactionInputs();
	virtual ~TransactionInputs();

	void addInput(const AbstractAddress* address, uint64_t amount);

private:
	ArrayList<TransactionInput>* inputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONINPUTS_H_ */
