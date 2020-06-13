/*
 * TransactionUpdateCache.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_
#define TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_

#include "base/HashMap.h"

using namespace alinous;

namespace codablecash {

class CdbOid;
class CdbTable;
class InsertLog;
class CdbRecord;
class InsertRecordsCacheCursor;
class TransactionTableUpdateCache;

class TransactionUpdateCache {
public:
	TransactionUpdateCache();
	virtual ~TransactionUpdateCache();

	void updateInsert(InsertLog* cmd, const CdbTable* table);

	void reset() noexcept;

	InsertRecordsCacheCursor* newCursor(const CdbTable* table) noexcept;

private:
	TransactionTableUpdateCache* getTransactionTableUpdateCache(const CdbTable* table) noexcept;

private:
	HashMap<CdbOid, TransactionTableUpdateCache>* tableCashes;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_ */
