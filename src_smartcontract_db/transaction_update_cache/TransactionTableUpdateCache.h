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

	void addInsertedRecord(const CdbRecord* newRecord) noexcept;
	InsertRecordsCacheCursor* newInsertedRecordCursor() const noexcept;

private:
	const CdbTable* table;

	InsertedRecordsRepository* insertedRecordRepo;
	UpdatedRecordsRepository* updatedRecordRepo;
	DeletedOidsRepository* deletedRecordRepo;

	CdbLocalCacheManager* cacheManager;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_ */
