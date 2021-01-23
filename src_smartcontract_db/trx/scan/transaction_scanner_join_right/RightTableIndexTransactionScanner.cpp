/*
 * RightTableIndexTransactionScanner.cpp
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableIndexTransactionScanner.h"

namespace codablecash {

RightTableIndexTransactionScanner::RightTableIndexTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
		const CdbTable* table, const AbstractScanCondition* filterCondition, CdbTableIndex* index)
			: AbstractTransactionScanner(metadata, trx, table, filterCondition){
	this->index = index;

}

RightTableIndexTransactionScanner::~RightTableIndexTransactionScanner() {
	this->index = nullptr;
}

void RightTableIndexTransactionScanner::start() {

}

void RightTableIndexTransactionScanner::reset(const AbstractCdbKey* key) {

}

bool RightTableIndexTransactionScanner::hasNext() {
	return false;
}

const CdbRecord* RightTableIndexTransactionScanner::next() {
	return nullptr;
}

void RightTableIndexTransactionScanner::shutdown() {
}

} /* namespace codablecash */
