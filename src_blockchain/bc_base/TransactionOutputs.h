/*
 * TransactionOutputs.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONOUTPUTS_H_
#define BC_BASE_TRANSACTIONOUTPUTS_H_

#include <inttypes.h>

#include "base/ArrayList.h"

namespace codablecash {
using namespace alinous;

class TransactionOutput;
class AbstractAddress;

class TransactionOutputs {
public:
	TransactionOutputs();
	virtual ~TransactionOutputs();

	void addOutput(const AbstractAddress* address, uint64_t amount) noexcept;
	uint64_t getTotalOutput() const noexcept;

private:
	ArrayList<TransactionOutput>* outputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONOUTPUTS_H_ */
