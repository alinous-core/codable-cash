/*
 * DeletedOidsRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_

namespace codablecash {

class CdbLocalCacheManager;

class DeletedOidsRepository {
public:
	explicit DeletedOidsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~DeletedOidsRepository();

};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_ */
