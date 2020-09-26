/*
 * SingleKeyOidCache.h
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_
#define TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_

#include "transaction_cache/AbstractSwapCache.h"

namespace codablecash {

class CdbKeyFactory;
class CdbDataFactory;

class SingleKeyOidCache : public AbstractSwapCache {
public:
	SingleKeyOidCache(const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~SingleKeyOidCache();

private:

};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_ */
