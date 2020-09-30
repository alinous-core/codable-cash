/*
 * InsertRecordRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class CdbLocalCacheManager;
class OidKeyRecordCache;
class CdbRecord;


class InsertedRecordsRepository {
public:
	explicit InsertedRecordsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~InsertedRecordsRepository();

	IBtreeScanner* getScanner();

	void addRecord(const CdbRecord* record);
private:
	OidKeyRecordCache* cache;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_ */
