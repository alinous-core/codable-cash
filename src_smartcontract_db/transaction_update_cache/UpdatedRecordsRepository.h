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
class CdbRecord;

class UpdatedRecordsRepository {
public:
	explicit UpdatedRecordsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~UpdatedRecordsRepository();

	bool hasNext() const noexcept;
	const CdbRecord* next() noexcept;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_UPDATEDRECORDSREPOSITORY_H_ */
