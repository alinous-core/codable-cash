/*
 * DeletedOidsRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "trx/scan/transaction_update_cache/DeletedOidsRepository.h"

#include "trx/transaction_cache/SingleKeyOidCache.h"

#include "engine/CdbLocalCacheManager.h"
#include "engine/CdbOid.h"

#include "schema_table/record/table_record_key/CdbOidKey.h"

#include "base/StackRelease.h"

namespace codablecash {

DeletedOidsRepository::DeletedOidsRepository(CdbLocalCacheManager* cacheManager) {
	this->cache = cacheManager->createSingleKeyOidCache();
}

DeletedOidsRepository::~DeletedOidsRepository() {
	delete this->cache;
}

IBtreeScanner* DeletedOidsRepository::getScanner() {
	return this->cache->getScanner();
}

void DeletedOidsRepository::addDeletedRecord(const CdbOid* recordOid) {
	const AbstractCdbKey* key = recordOid->toKey(); __STP(key);

	this->cache->insert(key, recordOid);
}

bool DeletedOidsRepository::isDeleted(const CdbOidKey* recordOidKey) {
	return this->cache->hasKey(recordOidKey);
}

} /* namespace codablecash */
