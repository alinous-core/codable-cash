/*
 * DeletedOidsRepository.h
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_
#define TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class CdbLocalCacheManager;
class SingleKeyOidCache;

class DeletedOidsRepository {
public:
	explicit DeletedOidsRepository(CdbLocalCacheManager* cacheManager);
	virtual ~DeletedOidsRepository();

	IBtreeScanner* getScanner();

private:
	SingleKeyOidCache* cache;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_DELETEDOIDSREPOSITORY_H_ */
