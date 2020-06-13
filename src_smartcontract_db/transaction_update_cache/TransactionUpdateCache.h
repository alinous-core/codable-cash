/*
 * TransactionUpdateCache.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_
#define TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class InsertLog;
class CdbRecord;

class TransactionUpdateCache {
public:
	TransactionUpdateCache();
	virtual ~TransactionUpdateCache();

	void updateInsert(InsertLog* cmd);

	void reset() noexcept;


private:
	ArrayList<CdbRecord>* insertedRecords;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_TRANSACTIONUPDATECACHE_H_ */
