/*
 * SingleKeyOidCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "transaction_cache/SingleKeyOidCache.h"

#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbDataFactory.h"

#include "table_record_key/AbstractCdbKey.h"

#include "engine/CdbOid.h"

namespace codablecash {

SingleKeyOidCache::SingleKeyOidCache(const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache)
			: AbstractSwapCache(name, keyFactory, dataFactory, diskCache) {

}

SingleKeyOidCache::~SingleKeyOidCache() {

}

void SingleKeyOidCache::insert(const AbstractCdbKey* key, const CdbOid* value) {
	const IBlockObject* lastObj = findData(key);

	int diff = 0;
	if(lastObj != nullptr){


		diff = lastObj->binarySize();

	}else{

	}

	this->currentSize += diff;
}


} /* namespace codablecash */
