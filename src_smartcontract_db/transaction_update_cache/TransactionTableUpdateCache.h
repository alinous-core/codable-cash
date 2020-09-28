/*
 * TransactionTableUpdateCache.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_
#define TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTable;
class CdbRecord;
class InsertRecordsCacheCursor;
class InsertedRecordsRepository;
class UpdatedRecordsRepository;
class CdbLocalCacheManager;
class DeletedOidsRepository;

class TransactionTableUpdateCache {
public:
	TransactionTableUpdateCache(const CdbTable* table, CdbLocalCacheManager* cacheManager);
	virtual ~TransactionTableUpdateCache();

	void addRecord(CdbRecord* newRecord) noexcept;
	void reset() noexcept;
	InsertRecordsCacheCursor* newCursor() const noexcept;

private:
	const CdbTable* table;

	InsertedRecordsRepository* inserts;
	UpdatedRecordsRepository* updates;
	DeletedOidsRepository* deletes;

	CdbLocalCacheManager* cacheManager;

	ArrayList<CdbRecord>* insertedRecords;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_ */
