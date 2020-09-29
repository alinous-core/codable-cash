/*
 * UpdateRecordRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class CdbLocalCacheManager;
class CdbRecord;
class OidKeyRecordCache;

class UpdatedRecordsRepository {
public:
	explicit UpdatedRecordsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~UpdatedRecordsRepository();

	IBtreeScanner* getScanner();

private:
	OidKeyRecordCache* cache;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_ */
