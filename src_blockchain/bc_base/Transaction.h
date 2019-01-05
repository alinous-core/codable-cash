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
class TransactionId;

class Transaction : public AbstractTransaction {
public:
	Transaction();
	virtual ~Transaction();

	void updateTransactionId();
	const TransactionId* getTransactionId() const noexcept;

	void addInput(const AbstractAddress* address, uint64_t amount) noexcept;
	void addOutput(const AbstractAddress* address, uint64_t amount) noexcept;
	void setFee(uint64_t amount) noexcept;

	uint64_t getTotalInput() const noexcept;
	uint64_t getTotalOutput() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static Transaction* fromBinary(ByteBuffer* in);
private:
	// id
	TransactionId* trxId;

	// body part
	uint64_t timelong;
	TransactionInputs* inputs;
	TransactionOutputs* outputs;
	BalanceUnit* fee;
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTION_H_ */
