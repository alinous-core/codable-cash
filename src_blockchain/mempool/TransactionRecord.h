/*
 * TransactionRecord.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONRECORD_H_
#define MEMPOOL_TRANSACTIONRECORD_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class TransactionRecord {
public:
	explicit TransactionRecord();
	virtual ~TransactionRecord();
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONRECORD_H_ */
