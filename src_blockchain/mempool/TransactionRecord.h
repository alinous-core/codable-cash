/*
 * TransactionRecord.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONRECORD_H_
#define MEMPOOL_TRANSACTIONRECORD_H_

#include "filestore_block/IBlockObject.h"

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class AbstractTransaction;

class TransactionRecord : public IBlockObject {
private:
	TransactionRecord();
public:
	explicit TransactionRecord(const AbstractTransaction* trx);
	virtual ~TransactionRecord();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static TransactionRecord* fromBinary(ByteBuffer* in);

	const AbstractTransaction* getTrx() const noexcept;
private:
	AbstractTransaction* trx;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONRECORD_H_ */
