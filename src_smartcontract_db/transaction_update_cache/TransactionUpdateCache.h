/*
 * TransactionUpdateCache.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_
#define TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_

#include "base/HashMap.h"

namespace alinous {
class File;
}  // namespace alinous
using namespace alinous;

namespace codablecash {

class CdbOid;
class CdbTable;
class InsertLog;
class CdbRecord;
class InsertRecordsCacheCursor;
class TransactionTableUpdateCache;
class CdbLocalCacheManager;
class LocalOidFactory;

class TransactionUpdateCache {
public:
	explicit TransactionUpdateCache(CdbLocalCacheManager* cacheManager, LocalOidFactory* localOidFacroty);
	virtual ~TransactionUpdateCache();

	void updateInsert(InsertLog* cmd, const CdbTable* table);

	void reset() noexcept;

	InsertRecordsCacheCursor* newInsertedRecordsCursor(const CdbTable* table) noexcept;

private:
	TransactionTableUpdateCache* getTransactionTableUpdateCache(const CdbTable* table) noexcept;

private:
	HashMap<CdbOid, TransactionTableUpdateCache>* tableCashes;

	CdbLocalCacheManager* cacheManager;
	LocalOidFactory* localOidFactory;

};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_ */
