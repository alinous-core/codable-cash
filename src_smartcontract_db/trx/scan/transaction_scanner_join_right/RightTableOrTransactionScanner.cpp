/*
 * RightTableOrTransactionScanner.cpp
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableOrTransactionScanner.h"

#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"


namespace codablecash {

RightTableOrTransactionScanner::RightTableOrTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table, const JoinOrCandidate* orCandidate)
		: AbstractTransactionScanner(metadata, trx, table){
	this->orCandidate = new JoinOrCandidate(*orCandidate);
}

RightTableOrTransactionScanner::~RightTableOrTransactionScanner() {
	delete this->orCandidate;
}

void RightTableOrTransactionScanner::start() {
}

void RightTableOrTransactionScanner::reset(const AbstractCdbKey* key) {
}

bool RightTableOrTransactionScanner::hasNext() {
	return false;
}

const CdbRecord* RightTableOrTransactionScanner::next() {
	return nullptr;
}

void RightTableOrTransactionScanner::shutdown() {
}


} /* namespace codablecash */
