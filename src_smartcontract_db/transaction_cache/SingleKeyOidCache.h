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

class CdbOid;
class AbstractCdbKey;

class SingleKeyOidCache : public AbstractSwapCache {
public:
	SingleKeyOidCache(const File* folder, const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~SingleKeyOidCache();

	void insert(const AbstractCdbKey* key, const CdbOid* value);
	bool hasKey(const AbstractCdbKey* key);

private:

};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_SINGLEKEYOIDCACHE_H_ */
