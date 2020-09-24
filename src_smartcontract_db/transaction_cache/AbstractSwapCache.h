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
class BtreeKeyFactory;
class AbstractBtreeDataFactory;
}
using namespace alinous;

namespace codablecash {

class AbstractSwapCache {
public:
	AbstractSwapCache(BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~AbstractSwapCache();

protected:
	BtreeKeyFactory* keyFactory;
	AbstractBtreeDataFactory* dataFactory;
	DiskCacheManager* diskCache;

	uint64_t currentSize;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_ */
