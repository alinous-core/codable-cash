/*
 * MemPool.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_MEMPOOL_H_
#define MEMPOOL_MEMPOOL_H_



namespace alinous {
class File;
class DiskCacheManager;
}

namespace codablecash {
using namespace alinous;

class TransactionStore;
class FeeIndex;
class TransactionIdIndex;

class MemPool {
public:
	MemPool(const File* baseDir);
	virtual ~MemPool();

	void init();
	void close();

private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	TransactionStore* store;
	FeeIndex* index;
	TransactionIdIndex* trxIdIndex;
};

} /* namespace codablecash */

#endif /* MEMPOOL_MEMPOOL_H_ */
