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
#include "filestore_block/IBlockObject.h"


namespace codablecash {
using namespace alinous;

class TransactionInput;
class AbstractAddress;

class TransactionInputs : public IBlockObject {
public:
	TransactionInputs(const TransactionInputs& inst);
	TransactionInputs();
	virtual ~TransactionInputs();

	void addInput(const AbstractAddress* address, uint64_t amount) noexcept;
	uint64_t getTotalInput() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	void importBinary(ByteBuffer* in);
private:
	ArrayList<TransactionInput>* inputs;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONINPUTS_H_ */
