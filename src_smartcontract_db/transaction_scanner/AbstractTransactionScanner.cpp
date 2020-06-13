/*
 * AbstractTransactionScanner.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "transaction_scanner/AbstractTransactionScanner.h"

#include "transaction/CdbTransaction.h"

#include "transaction_update_cache/InsertRecordsCacheCursor.h"
#include "transaction_update_cache/TransactionUpdateCache.h"


namespace codablecash {

AbstractTransactionScanner::AbstractTransactionScanner(CdbTransaction* trx) {
	this->trx = trx;

	TransactionUpdateCache* cache = this->trx->getUpdateCache();
	this->cacheCursor = cache->newCursor();
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
