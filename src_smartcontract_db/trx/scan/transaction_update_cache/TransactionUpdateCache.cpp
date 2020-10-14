/*
 * TransactionUpdateCache.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "trx/scan/transaction_update_cache/TransactionUpdateCache.h"
#include "trx/scan/transaction_update_cache/InsertRecordsCacheCursor.h"
#include "trx/scan/transaction_update_cache/TransactionTableUpdateCache.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "trx/transaction_log/InsertLog.h"

#include "engine/CdbLocalCacheManager.h"
#include "engine/CdbOid.h"

#include "base/StackRelease.h"

#include "schema_table/table/CdbTable.h"

#include "base_io/File.h"

#include "schema_table/record/table_record_local/LocalOidFactory.h"
#include "schema_table/record/table_record_value/VmInstanceValueConverter.h"

namespace codablecash {

TransactionUpdateCache::TransactionUpdateCache(CdbLocalCacheManager* cacheManager, LocalOidFactory* localOidFacroty) {
	this->tableCashes = new HashMap<CdbOid, TransactionTableUpdateCache>();
	this->cacheManager = cacheManager;
	this->localOidFactory = localOidFacroty;
}

TransactionUpdateCache::~TransactionUpdateCache() {
	reset();
	delete this->tableCashes;
	this->cacheManager = nullptr;
	this->localOidFactory = nullptr;
}

void TransactionUpdateCache::reset() noexcept {
	Iterator<CdbOid>* it = this->tableCashes->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		TransactionTableUpdateCache* c = this->tableCashes->get(oid);
		delete c;
	}

	this->tableCashes->clear();
}

TransactionTableUpdateCache* TransactionUpdateCache::getTransactionTableUpdateCache(const CdbTable* table) noexcept {
	const CdbOid* oid = table->getOid();
	TransactionTableUpdateCache* cache = this->tableCashes->get(oid);

	if(cache == nullptr){
		cache = new TransactionTableUpdateCache(table, this->cacheManager);
		this->tableCashes->put(oid, cache);
	}

	return cache;
}

void TransactionUpdateCache::updateInsert(InsertLog* cmd, const CdbTable* table) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	const ArrayList<CdbRecord>* list = cmd->getRecords();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* record = list->get(i);

	//	CdbRecord* newRecord = dynamic_cast<CdbRecord*>(record->copy()); __STP(newRecord);

		c->addInsertedRecord(record);
	}
}

InsertRecordsCacheCursor* TransactionUpdateCache::newInsertedRecordsCursor(const CdbTable* table) noexcept {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->newInsertedRecordCursor();
}

void TransactionUpdateCache::addDeletedRecord(const CdbTable* table, const CdbOid* recordOid) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	c->addDeletedRecord(recordOid);
}

bool TransactionUpdateCache::isDeleted(const CdbTable* table, const CdbOid* recordOid) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->isDeleted(recordOid);
}

DeletedRecordsOidsCursor* TransactionUpdateCache::getDeletedRecordsOidsCursor(const CdbTable* table) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->getDeletedRecordsOidsCursor();
}

void TransactionUpdateCache::addUpdatedRecord(const CdbTable* table, const CdbRecord* updatedRecord) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	c->addUpdatedRecord(updatedRecord);
}

bool TransactionUpdateCache::isUpdated(const CdbTable* table, const CdbOid* recordOid) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->isUpdated(recordOid);
}

const CdbRecord* TransactionUpdateCache::getUpdatedRecord(const CdbTable* table, const CdbOid* recordOid) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->getUpdatedRecord(recordOid);
}

UpdatedRecordCursor* TransactionUpdateCache::getUpdatedRecordCursor(const CdbTable* table) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->getUpdatedRecordCursor();
}


} /* namespace codablecash */
