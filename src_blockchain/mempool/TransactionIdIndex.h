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
class DiskCacheManager;
class Btree;
}

namespace codablecash {
using namespace alinous;

class TransactionIdIndex {
public:
	TransactionIdIndex(File* baseDir, DiskCacheManager* cacheManager);
	virtual ~TransactionIdIndex();

private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	Btree* btree;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONIDINDEX_H_ */
