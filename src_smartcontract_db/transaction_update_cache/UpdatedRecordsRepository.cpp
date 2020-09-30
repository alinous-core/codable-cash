/*
 * UpdateRecordRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "transaction_update_cache/UpdatedRecordsRepository.h"

#include "transaction_cache/OidKeyRecordCache.h"

#include "engine/CdbLocalCacheManager.h"

#include "table_record_key/CdbOidKey.h"

#include "table_record/CdbRecord.h"

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

void UpdatedRecordsRepository::addUpdatedRecord(const CdbRecord* updatedRecord) {
	this->cache->insert(updatedRecord);
}

bool UpdatedRecordsRepository::isUpdated(const CdbOidKey* recordOidKey) {
	return this->cache->hasKey(recordOidKey);
}

const CdbRecord* UpdatedRecordsRepository::getUpdatedRecord(const CdbOidKey* recordOidKey) {
	return this->cache->findRecord(recordOidKey);
}


} /* namespace codablecash */
