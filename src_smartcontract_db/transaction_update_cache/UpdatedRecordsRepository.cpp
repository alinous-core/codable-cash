/*
 * UpdateRecordRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "transaction_update_cache/UpdatedRecordsRepository.h"

#include "transaction_cache/OidKeyRecordCache.h"

#include "engine/CdbLocalCacheManager.h"

namespace codablecash {

UpdatedRecordsRepository::UpdatedRecordsRepository(CdbLocalCacheManager* cacheManager) {
	this->cache = cacheManager->createOidKeyRecordCache();
}

UpdatedRecordsRepository::~UpdatedRecordsRepository() {
	delete this->cache;
}

IBtreeScanner* UpdatedRecordsRepository::getScanner() {
	return this->cache->getScanner();
}

} /* namespace codablecash */
