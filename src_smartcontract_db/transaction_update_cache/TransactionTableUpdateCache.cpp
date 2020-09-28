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

	this->inserts = new InsertedRecordsRepository(cacheManager);
	this->updates = new UpdatedRecordsRepository(cacheManager);
	this->deletes = new DeletedOidsRepository(cacheManager);

	this->insertedRecords = new ArrayList<CdbRecord>();
}

TransactionTableUpdateCache::~TransactionTableUpdateCache() {
	this->table = nullptr;
	this->cacheManager = nullptr;

	delete this->inserts;
	delete this->updates;
	delete this->deletes;

	reset();
	delete this->insertedRecords;
}

void TransactionTableUpdateCache::reset() noexcept {
	this->insertedRecords->deleteElements();
	this->insertedRecords->reset();
}

void TransactionTableUpdateCache::addRecord(CdbRecord* newRecord) noexcept {
	this->insertedRecords->addElement(newRecord);
}

InsertRecordsCacheCursor* TransactionTableUpdateCache::newCursor() const noexcept {
	return new InsertRecordsCacheCursor(this->insertedRecords);
}

} /* namespace codablecash */
