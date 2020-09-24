/*
 * AbstractSwapCache.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_
#define TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_
#include <cstdint>

namespace alinous {
class DiskCacheManager;
}
using namespace alinous;

namespace codablecash {

class CdbKeyFactory;
class CdbDataFactory;

class AbstractSwapCache {
public:
	AbstractSwapCache(CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory);
	virtual ~AbstractSwapCache();

protected:
	CdbKeyFactory* keyFactory;
	CdbDataFactory* dataFactory;
	DiskCacheManager* diskCache;

	uint64_t currentSize;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_ */
