/*
 * AbstractTransactionScanner.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/scan/transaction_update_cache/InsertRecordsCacheCursor.h"
#include "trx/scan/transaction_update_cache/TransactionUpdateCache.h"

#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"

#include "schema_table/table/CdbTable.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

namespace codablecash {

AbstractTransactionScanner::AbstractTransactionScanner(const ScanResultMetadata* metadata,
		CdbTransaction* trx, const CdbTable* table, const AbstractScanCondition* filterCondition) {
	this->metadata = new ScanResultMetadata(*metadata);
	this->trx = trx;
	this->table = table;
	this->filterCondition = filterCondition != nullptr ? filterCondition->cloneCondition() : nullptr;

	TransactionUpdateCache* cache = this->trx->getUpdateCache();
	this->cacheCursor = cache->newInsertedRecordsCursor(table);

}

AbstractTransactionScanner::~AbstractTransactionScanner() {
	delete metadata;
	this->trx = nullptr;
	this->table = nullptr;
	delete this->cacheCursor;
	delete this->filterCondition;
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
