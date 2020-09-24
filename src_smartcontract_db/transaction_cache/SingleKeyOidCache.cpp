/*
 * SingleKeyOidCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/SingleKeyOidCache.h"

#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbDataFactory.h"

namespace codablecash {

SingleKeyOidCache::SingleKeyOidCache(CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache)
			: AbstractSwapCache(keyFactory, dataFactory, diskCache) {

}

SingleKeyOidCache::~SingleKeyOidCache() {

}

} /* namespace codablecash */
