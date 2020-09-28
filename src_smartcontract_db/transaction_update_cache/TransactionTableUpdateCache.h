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

class TransactionTableUpdateCache {
public:
	explicit TransactionTableUpdateCache(const CdbTable* table);
	virtual ~TransactionTableUpdateCache();

	void addRecord(CdbRecord* newRecord) noexcept;
	void reset() noexcept;
	InsertRecordsCacheCursor* newCursor() const noexcept;

private:
	const CdbTable* table;

	InsertedRecordsRepository* inserts;
	UpdatedRecordsRepository* updates;

	ArrayList<CdbRecord>* insertedRecords;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONTABLEUPDATECACHE_H_ */
