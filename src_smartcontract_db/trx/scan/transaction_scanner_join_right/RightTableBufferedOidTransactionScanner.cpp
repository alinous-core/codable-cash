/*
 * RightTableBufferedOidTransactionScanner.cpp
 *
 *  Created on: 2020/12/24
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableBufferedOidTransactionScanner.h"

namespace codablecash {

RightTableBufferedOidTransactionScanner::RightTableBufferedOidTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
		const CdbTable* table, const AbstractScanCondition* filterCondition)
		: AbstractTransactionScanner(metadata, trx, table, filterCondition){

}

RightTableBufferedOidTransactionScanner::~RightTableBufferedOidTransactionScanner() {

}

void RightTableBufferedOidTransactionScanner::start() {
}

void RightTableBufferedOidTransactionScanner::reset(const AbstractCdbKey* key) {
}

bool RightTableBufferedOidTransactionScanner::hasNext() {
	return false;
}

const CdbRecord* RightTableBufferedOidTransactionScanner::next() {
	return nullptr;
}

void RightTableBufferedOidTransactionScanner::shutdown() {
}

} /* namespace codablecash */
