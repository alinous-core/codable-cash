/*
 * OidKeyRecordCache.h
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_CACHE_OIDKEYRECORDCACHE_H_
#define TRANSACTION_CACHE_OIDKEYRECORDCACHE_H_

#include "transaction_cache/AbstractSwapCache.h"

namespace codablecash {

class CdbKeyFactory;
class CdbDataFactory;
class CdbOidKey;
class CdbRecord;

class OidKeyRecordCache : public AbstractSwapCache {
public:
	OidKeyRecordCache(const File* folder, const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache);
	virtual ~OidKeyRecordCache();

	void insert(const CdbRecord* value);
	bool hasKey(const CdbOidKey* key);
	const CdbRecord* findRecord(const CdbOidKey* key);
};

} /* namespace codablecash */

#endif /* TRANSACTION_CACHE_OIDKEYRECORDCACHE_H_ */
