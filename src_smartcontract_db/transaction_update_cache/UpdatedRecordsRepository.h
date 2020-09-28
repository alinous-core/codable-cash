/*
 * UpdateRecordRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_

namespace codablecash {

class CdbLocalCacheManager;

class UpdatedRecordsRepository {
public:
	explicit UpdatedRecordsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~UpdatedRecordsRepository();
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_ */
