/*
 * TransactionIdIndex.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONIDINDEX_H_
#define MEMPOOL_TRANSACTIONIDINDEX_H_

#include <cstdint>

namespace alinous {
class File;
class DiskCacheManager;
class Btree;
}

namespace codablecash {
using namespace alinous;

class TransactionId;

class TransactionIdIndex {
public:
	static const constexpr wchar_t* FILE_NAME{L"idx_trx"};

	TransactionIdIndex(File* baseDir, DiskCacheManager* cacheManager);
	virtual ~TransactionIdIndex();

	bool exists() const noexcept;
	void create() noexcept(false);

	void open() noexcept(false);
	void close() noexcept;

	void addIndex(const TransactionId* trxId, uint64_t fpos);
	uint64_t findbyTransactionId(const TransactionId* trxId) const;
	void removeTransaction(const TransactionId* trxId);

private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	Btree* btree;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONIDINDEX_H_ */
