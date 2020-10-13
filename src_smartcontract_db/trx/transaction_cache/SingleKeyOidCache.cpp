/*
 * SingleKeyOidCache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "trx/transaction_cache/SingleKeyOidCache.h"

#include "schema_table/table_record/CdbKeyFactory.h"
#include "schema_table/table_record/CdbDataFactory.h"

#include "schema_table/table_record_key/AbstractCdbKey.h"

#include "schema_table/table_record_value/CdbOidValueList.h"

#include "engine/CdbOid.h"

#include "base/StackRelease.h"

namespace codablecash {

SingleKeyOidCache::SingleKeyOidCache(const File* folder, const UnicodeString* name, CdbKeyFactory* keyFactory, CdbDataFactory* dataFactory, DiskCacheManager* diskCache)
			: AbstractSwapCache(folder, name, keyFactory, dataFactory, diskCache) {

}

SingleKeyOidCache::~SingleKeyOidCache() {

}

void SingleKeyOidCache::insert(const AbstractCdbKey* key, const CdbOid* value) {
	const IBlockObject* lastObj = findData(key);

	int diff = 0;
	if(lastObj != nullptr){
		int lastSize = lastObj->binarySize();
		CdbOidValueList* oidList = dynamic_cast<CdbOidValueList*>(lastObj->copyData()); __STP(oidList);
		oidList->addOid(value->copy());

		putData(key, oidList);

		diff = oidList->binarySize() - lastSize;
	}else{
		CdbOidValueList* oidList = new CdbOidValueList(); __STP(oidList);
		oidList->addOid(value->copy());

		putData(key, oidList);

		diff = oidList->binarySize();
	}

	this->currentSize += diff;

	swapIfNecessary();
}

bool SingleKeyOidCache::hasKey(const AbstractCdbKey* key) {
	const IBlockObject* lastObj = findData(key);

	return lastObj != nullptr;
}

} /* namespace codablecash */
