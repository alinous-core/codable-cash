/*
 * TransactionIdIndex.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONIDINDEX_H_
#define MEMPOOL_TRANSACTIONIDINDEX_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class TransactionIdIndex {
public:
	TransactionIdIndex(File* baseDir);
	virtual ~TransactionIdIndex();

private:
	File* baseDir;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONIDINDEX_H_ */
