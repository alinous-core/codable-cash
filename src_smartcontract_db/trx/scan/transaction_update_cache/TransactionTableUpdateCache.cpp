/*
 * TransactionTableUpdateCache.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "trx/scan/transaction_update_cache/TransactionTableUpdateCache.h"
#include "trx/scan/transaction_update_cache/InsertRecordsCacheCursor.h"
#include "trx/scan/transaction_update_cache/InsertedRecordsRepository.h"
#include "trx/scan/transaction_update_cache/UpdatedRecordsRepository.h"
#include "trx/scan/transaction_update_cache/DeletedOidsRepository.h"
#include "trx/scan/transaction_update_cache/UpdatedRecordCursor.h"
#include "trx/scan/transaction_update_cache/DeletedRecordsOidsCursor.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_key/CdbOidKey.h"
#include "schema_table/record/table_record_key/AbstractCdbKey.h"

#include "base/StackRelease.h"

#include "engine/CdbOid.h"

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

void TransactionTableUpdateCache::addDeletedRecord(const CdbOid* recordOid) {
	this->deletedRecordRepo->addDeletedRecord(recordOid);
}

bool TransactionTableUpdateCache::isDeleted(const CdbOid* recordOid) {
	AbstractCdbKey* abkey = recordOid->toKey(); __STP(abkey);
	CdbOidKey* key = dynamic_cast<CdbOidKey*>(abkey);

	return isDeleted(key);
}

bool TransactionTableUpdateCache::isDeleted(const CdbOidKey* recordOidKey) {
	return this->deletedRecordRepo->isDeleted(recordOidKey);
}

DeletedRecordsOidsCursor* TransactionTableUpdateCache::getDeletedRecordsOidsCursor() {
	return new DeletedRecordsOidsCursor(this->deletedRecordRepo);
}

void TransactionTableUpdateCache::addUpdatedRecord(const CdbRecord* updatedRecord) {
	this->updatedRecordRepo->addUpdatedRecord(updatedRecord);
}

bool TransactionTableUpdateCache::isUpdated(const CdbOid* recordOid) {
	AbstractCdbKey* abkey = recordOid->toKey(); __STP(abkey);
	CdbOidKey* key = dynamic_cast<CdbOidKey*>(abkey);

	return isUpdated(key);
}

bool TransactionTableUpdateCache::isUpdated(const CdbOidKey* recordOidKey) {
	return this->updatedRecordRepo->isUpdated(recordOidKey);
}

const CdbRecord* TransactionTableUpdateCache::getUpdatedRecord(const CdbOid* recordOid) {
	AbstractCdbKey* abkey = recordOid->toKey(); __STP(abkey);
	CdbOidKey* key = dynamic_cast<CdbOidKey*>(abkey);

	return getUpdatedRecord(key);
}

const CdbRecord* TransactionTableUpdateCache::getUpdatedRecord(const CdbOidKey* recordOidKey) {
	return this->updatedRecordRepo->getUpdatedRecord(recordOidKey);
}

UpdatedRecordCursor* TransactionTableUpdateCache::getUpdatedRecordCursor() {
	return new UpdatedRecordCursor(this->updatedRecordRepo);
}

} /* namespace codablecash */
