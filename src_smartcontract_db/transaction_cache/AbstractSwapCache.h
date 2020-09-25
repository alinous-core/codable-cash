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
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class AbstractSwapCache {
public:
	AbstractSwapCache(const UnicodeString* name, BtreeKeyFactory* keyFactory, AbstractBtreeDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~AbstractSwapCache();

	void setSwappiness(int swappiness) {
		this->swappiness = swappiness;
	}

protected:
	UnicodeString* name;
	BtreeKeyFactory* keyFactory;
	AbstractBtreeDataFactory* dataFactory;
	DiskCacheManager* diskCache;

	uint64_t currentSize;
	int swappiness;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_ABSTRACTSWAPCACHE_H_ */
