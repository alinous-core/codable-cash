/*
 * Transaction.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTION_H_
#define BC_BASE_TRANSACTION_H_

#include <cstdint>

#include "bc_base/AbstractTransaction.h"

namespace codablecash {

class TransactionInputs;
class TransactionOutputs;
class BalanceUnit;
class AbstractAddress;
class TransactionId;

class Transaction : public AbstractTransaction {
public:
	Transaction(const Transaction& inst);
	Transaction();
	virtual ~Transaction();

	virtual void updateTransactionId();
	virtual const TransactionId* getTransactionId() const noexcept;

	void addInput(const AbstractAddress* address, uint64_t amount) noexcept;
	void addOutput(const AbstractAddress* address, uint64_t amount) noexcept;
	void setFee(const BalanceUnit& amount) noexcept;

	uint64_t getTotalInput() const noexcept;
	uint64_t getTotalOutput() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static Transaction* fromBinary(ByteBuffer* in);

	virtual AbstractTransaction* clone() const;
	virtual const BalanceUnit* getFee() const noexcept;
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
