/*
 * AbstractTransactionScanner.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "trx/transaction_scanner/AbstractTransactionScanner.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/transaction_update_cache/InsertRecordsCacheCursor.h"
#include "trx/transaction_update_cache/TransactionUpdateCache.h"

#include "schema_table/table/CdbTable.h"

namespace codablecash {

AbstractTransactionScanner::AbstractTransactionScanner(CdbTransaction* trx, const CdbTable* table) {
	this->trx = trx;
	this->table = table;

	TransactionUpdateCache* cache = this->trx->getUpdateCache();
	this->cacheCursor = cache->newInsertedRecordsCursor(table);

}

AbstractTransactionScanner::~AbstractTransactionScanner() {
	this->trx = nullptr;
	delete this->cacheCursor;
}

bool AbstractTransactionScanner::hasInsertedRecord() const noexcept {
	return this->cacheCursor->hasNext();
}

const CdbRecord* AbstractTransactionScanner::nextInsertedRecord() noexcept {
	return this->cacheCursor->next();
}

const CdbRecord* AbstractTransactionScanner::checkUpdated(const CdbRecord* record) const noexcept {
	// FIXME updated
	return record;
}

} /* namespace codablecash */
