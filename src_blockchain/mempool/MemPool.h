/*
 * MemPool.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_MEMPOOL_H_
#define MEMPOOL_MEMPOOL_H_

#include <inttypes.h>

namespace alinous {
class File;
class DiskCacheManager;
class ConcurrentGate;
}

namespace codablecash {
using namespace alinous;

class TransactionStore;
class FeeIndex;
class TransactionIdIndex;
class AbstractTransaction;
class FposValue;
class TransactionId;
class TransactionRecord;

class MemPool {
public:
	explicit MemPool(const File* baseDir);
	MemPool(const File* baseDir, int cacheBytes);
	virtual ~MemPool();

	void init();
	void close();

	void addTransaction(const AbstractTransaction* trx);
	bool removeTransaction(const TransactionId* trxId);
	TransactionRecord* findByTransactionId(const TransactionId* trxId);

private:
	TransactionRecord* __findByTransactionId(const TransactionId* trxId, uint64_t* outfpos);

private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	TransactionStore* store;
	FeeIndex* feeIndex;
	TransactionIdIndex* trxIdIndex;

	ConcurrentGate* rwLock;
};

} /* namespace codablecash */

#endif /* MEMPOOL_MEMPOOL_H_ */
