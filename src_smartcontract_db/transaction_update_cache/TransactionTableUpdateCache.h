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
class CdbOid;
class CdbOidKey;
class DeletedRecordsOidsCursor;
class UpdatedRecordCursor;

class TransactionTableUpdateCache {
public:
	TransactionTableUpdateCache(const CdbTable* table, CdbLocalCacheManager* cacheManager);
	virtual ~TransactionTableUpdateCache();

	void addInsertedRecord(const CdbRecord* newRecord) noexcept;
	InsertRecordsCacheCursor* newInsertedRecordCursor() const noexcept;

	void addDeletedRecord(const CdbOid* recordOid);
	bool isDeleted(const CdbOid* recordOid);
	bool isDeleted(const CdbOidKey* recordOidKey);
	DeletedRecordsOidsCursor* getDeletedRecordsOidsCursor();

	void addUpdatedRecord(const CdbRecord* updatedRecord);
	bool isUpdated(const CdbOid* recordOid);
	bool isUpdated(const CdbOidKey* recordOidKey);
	const CdbRecord* getUpdatedRecord(const CdbOid* recordOid);
	const CdbRecord* getUpdatedRecord(const CdbOidKey* recordOidKey);
	UpdatedRecordCursor* getUpdatedRecordCursor();

private:
	const CdbTable* table;

	InsertedRecordsRepository* insertedRecordRepo;
	UpdatedRecordsRepository* updatedRecordRepo;
	DeletedOidsRepository* deletedRecordRepo;

	CdbLocalCacheManager* cacheManager;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_ */
