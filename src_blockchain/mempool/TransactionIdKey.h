/*
 * TransactionIdKey.h
 *
 *  Created on: 2019/01/13
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONIDKEY_H_
#define MEMPOOL_TRANSACTIONIDKEY_H_

#include "btree/AbstractBtreeKey.h"

#include <inttypes.h>

namespace codablecash {
using namespace alinous;

class TransactionId;

class TransactionIdKey : public AbstractBtreeKey {
private:
	TransactionIdKey();
public:
	explicit TransactionIdKey(const TransactionId* trxId);
	virtual ~TransactionIdKey();

	virtual bool isInfinity() const;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;
	virtual AbstractBtreeKey* clone()  const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static TransactionIdKey* fromBinary(ByteBuffer* in);

private:
	TransactionId* trxId;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONIDKEY_H_ */
