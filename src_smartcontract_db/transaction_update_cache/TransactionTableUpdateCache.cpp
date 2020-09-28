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

#include "table_record/CdbRecord.h"

namespace codablecash {

TransactionTableUpdateCache::TransactionTableUpdateCache(const CdbTable* table) {
	this->table = table;

	this->inserts = new InsertedRecordsRepository();
	this->updates = new UpdatedRecordsRepository();

	this->insertedRecords = new ArrayList<CdbRecord>();
}

TransactionTableUpdateCache::~TransactionTableUpdateCache() {
	this->table = nullptr;

	delete this->inserts;
	delete this->updates;

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
