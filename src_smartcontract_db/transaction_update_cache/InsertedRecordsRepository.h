/*
 * InsertRecordRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_

namespace codablecash {

class CdbLocalCacheManager;

class InsertedRecordsRepository {
public:
	explicit InsertedRecordsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~InsertedRecordsRepository();
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_INSERTEDRECORDSREPOSITORY_H_ */
