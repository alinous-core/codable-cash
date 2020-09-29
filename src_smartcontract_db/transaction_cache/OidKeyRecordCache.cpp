/*
 * OidKeyRecordCache.cpp
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#include "transaction_cache/OidKeyRecordCache.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbDataFactory.h"
#include "table_record/CdbRecord.h"

#include "table_record_key/CdbOidKey.h"

#include "random_access_file/DiskCacheManager.h"

#include "engine/CdbOid.h"
#include "engine/CdbException.h"

namespace codablecash {

OidKeyRecordCache::OidKeyRecordCache(const File* folder, const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache)
			: AbstractSwapCache(folder, name, keyFactory, dataFactory, diskCache) {

}

OidKeyRecordCache::~OidKeyRecordCache() {

}

void OidKeyRecordCache::insert(const CdbRecord* value) {
	const CdbOid* oid = value->getOid();
	AbstractCdbKey* key = oid->toKey(); __STP(key);

	if(hasKey(dynamic_cast<const CdbOidKey*>(key))){
		throw new CdbException(L"Key is already stored in cache.", __FILE__, __LINE__);
	}

	int diff = value->binarySize();
	putData(key, value);

	this->currentSize += diff;
	swapIfNecessary();
}

bool OidKeyRecordCache::hasKey(const CdbOidKey* key) {
	const IBlockObject* data = findData(key);

	return data != nullptr;
}

} /* namespace codablecash */
