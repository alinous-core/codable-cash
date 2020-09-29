/*
 * TransactionTableUpdateCache.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_update_cache/TransactionTableUpdateCache.h"
#include "transaction_update_cache/InsertRecordsCacheCursor.h"
#include "transaction_update_cache/InsertedRecordsRepository.h"
#include "transaction_update_cache/UpdatedRecordsRepository.h"
#include "transaction_update_cache/DeletedOidsRepository.h"

#include "table_record/CdbRecord.h"

namespace codablecash {

TransactionTableUpdateCache::TransactionTableUpdateCache(const CdbTable* table, CdbLocalCacheManager* cacheManager) {
	this->table = table;
	this->cacheManager = cacheManager;

	this->insertedRecordRepo = new InsertedRecordsRepository(cacheManager);
	this->updatedRecordRepo = new UpdatedRecordsRepository(cacheManager);
	this->deletedRecordRepo = new DeletedOidsRepository(cacheManager);
}

TransactionTableUpdateCache::~TransactionTableUpdateCache() {
	this->table = nullptr;
	this->cacheManager = nullptr;

	delete this->insertedRecordRepo;
	delete this->updatedRecordRepo;
	delete this->deletedRecordRepo;
}

void TransactionTableUpdateCache::addInsertedRecord(const CdbRecord* newRecord) noexcept {
	this->insertedRecordRepo->addRecord(newRecord);
}

InsertRecordsCacheCursor* TransactionTableUpdateCache::newInsertedRecordCursor() const noexcept {
	return new InsertRecordsCacheCursor(this->insertedRecordRepo);
}

} /* namespace codablecash */
