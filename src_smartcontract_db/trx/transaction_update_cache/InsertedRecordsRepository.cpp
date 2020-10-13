/*
 * InsertRecordRepository.cpp
 *
 *  Created on: 2020/09/28
 *      Author: iizuka
 */

#include "trx/transaction_update_cache/InsertedRecordsRepository.h"

#include "engine/CdbLocalCacheManager.h"

#include "trx/transaction_cache/OidKeyRecordCache.h"

#include "btree/IBtreeScanner.h"

namespace codablecash {

InsertedRecordsRepository::InsertedRecordsRepository(CdbLocalCacheManager* cacheManager) {
	this->cache = cacheManager->createOidKeyRecordCache();
}

InsertedRecordsRepository::~InsertedRecordsRepository() {
	delete this->cache;
}

IBtreeScanner* InsertedRecordsRepository::getScanner() {
	return this->cache->getScanner();
}

void codablecash::InsertedRecordsRepository::addRecord(const CdbRecord* record) {
	this->cache->insert(record);
}

} /* namespace codablecash */
