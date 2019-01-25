/*
 * TransactionStore.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef MEMPOOL_TRANSACTIONSTORE_H_
#define MEMPOOL_TRANSACTIONSTORE_H_

#include <cstdint>

namespace alinous {
class File;
class BlockFileStore;
class DiskCacheManager;
}

namespace codablecash {
using namespace alinous;

class TransactionRecord;

class TransactionStore {
public:
	static const constexpr wchar_t* FILE_NAME{L"mempool"};

	TransactionStore(const File* baseDir, DiskCacheManager* cacheManager);
	virtual ~TransactionStore();

	bool exists() const noexcept;
	void create() noexcept(false);

	void open() noexcept(false);
	void close() noexcept;

	uint64_t storeTransaction(const TransactionRecord* record);
	TransactionRecord* loadRecord(uint64_t fpos);

private:
	File getStoreFile() const noexcept;
	File getStoreHeaderFile() const noexcept;
private:
	File* baseDir;
	DiskCacheManager* cacheManager;
	BlockFileStore* store;
};

} /* namespace codablecash */

#endif /* MEMPOOL_TRANSACTIONSTORE_H_ */
