/*
 * DeletedOidsRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "transaction_update_cache/DeletedOidsRepository.h"

#include "transaction_cache/SingleKeyOidCache.h"

#include "engine/CdbLocalCacheManager.h"


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

} /* namespace codablecash */
