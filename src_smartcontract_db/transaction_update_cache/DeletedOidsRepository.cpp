/*
 * DeletedOidsRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "transaction_update_cache/DeletedOidsRepository.h"

#include "transaction_cache/SingleKeyOidCache.h"

#include "engine/CdbLocalCacheManager.h"
#include "engine/CdbOid.h"

#include "table_record_key/CdbOidKey.h"

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
	const AbstractCdbKey* key = recordOid->toKey();

	this->cache->insert(key, recordOid);
}

bool DeletedOidsRepository::isDeleted(const CdbOidKey* recordOidKey) {
	return this->cache->hasKey(recordOidKey);
}

} /* namespace codablecash */
