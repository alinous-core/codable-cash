/*
 * TransactionUpdateCache.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_update_cache/TransactionUpdateCache.h"
#include "transaction_update_cache/InsertRecordsCacheCursor.h"

#include "table_record/CdbRecord.h"

#include "transaction_log/InsertLog.h"


namespace codablecash {

TransactionUpdateCache::TransactionUpdateCache() {
	this->insertedRecords = new ArrayList<CdbRecord>();
}

TransactionUpdateCache::~TransactionUpdateCache() {
	reset();
	delete this->insertedRecords;
}

void TransactionUpdateCache::updateInsert(InsertLog* cmd) {
	const ArrayList<CdbRecord>* list = cmd->getRecords();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* record = list->get(i);

		CdbRecord* newRecord = dynamic_cast<CdbRecord*>(record->copy());
		this->insertedRecords->addElement(newRecord);
	}
}

void TransactionUpdateCache::reset() noexcept {
	this->insertedRecords->deleteElements();
	this->insertedRecords->reset();
}



InsertRecordsCacheCursor* TransactionUpdateCache::newCursor() const noexcept {
	return new InsertRecordsCacheCursor(this->insertedRecords);
}


} /* namespace codablecash */
