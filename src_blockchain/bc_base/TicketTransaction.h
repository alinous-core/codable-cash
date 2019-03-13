/*
 * TicketTransaction.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef BC_BASE_TICKETTRANSACTION_H_
#define BC_BASE_TICKETTRANSACTION_H_

#include <cstdint>
#include "AbstractTransaction.h"

namespace codablecash {

class Nonce;
class TransactionId;

class TicketTransaction : public AbstractTransaction {
public:
	explicit TicketTransaction(uint64_t fheight);
	virtual ~TicketTransaction();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual AbstractTransaction* clone() const;

	virtual void updateTransactionId();
	virtual const TransactionId* getTransactionId() const noexcept;
	virtual const BalanceUnit* getFee() const noexcept;

private:
	Nonce* nonce;
	uint64_t fheight;
	BalanceUnit* fee;

	TransactionId* trxId;

};

} /* namespace codablecash */

#endif /* BC_BASE_TICKETTRANSACTION_H_ */
