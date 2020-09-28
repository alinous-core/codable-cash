/*
 * TransactionUpdateCache.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_update_cache/TransactionUpdateCache.h"
#include "transaction_update_cache/InsertRecordsCacheCursor.h"
#include "transaction_update_cache/TransactionTableUpdateCache.h"

#include "table_record/CdbRecord.h"

#include "transaction_log/InsertLog.h"

#include "engine/CdbOid.h"

#include "base/StackRelease.h"

#include "table/CdbTable.h"

#include "base_io/File.h"

namespace codablecash {

TransactionUpdateCache::TransactionUpdateCache(const File* tmpFolder) {
	this->tableCashes = new HashMap<CdbOid, TransactionTableUpdateCache>();
	this->tmpFolder = new File(*tmpFolder);
}

TransactionUpdateCache::~TransactionUpdateCache() {
	reset();
	delete this->tableCashes;
	delete this->tmpFolder;
}

void TransactionUpdateCache::updateInsert(InsertLog* cmd, const CdbTable* table) {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	const ArrayList<CdbRecord>* list = cmd->getRecords();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* record = list->get(i);

		CdbRecord* newRecord = dynamic_cast<CdbRecord*>(record->copy());
		c->addRecord(newRecord);
	}
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

InsertRecordsCacheCursor* TransactionUpdateCache::newCursor(const CdbTable* table) noexcept {
	TransactionTableUpdateCache* c = getTransactionTableUpdateCache(table);

	return c->newCursor();
}

TransactionTableUpdateCache* TransactionUpdateCache::getTransactionTableUpdateCache(const CdbTable* table) noexcept {
	const CdbOid* oid = table->getOid();
	TransactionTableUpdateCache* cache = this->tableCashes->get(oid);

	if(cache == nullptr){
		cache = new TransactionTableUpdateCache(table);
		this->tableCashes->put(oid, cache);
	}

	return cache;
}

} /* namespace codablecash */
