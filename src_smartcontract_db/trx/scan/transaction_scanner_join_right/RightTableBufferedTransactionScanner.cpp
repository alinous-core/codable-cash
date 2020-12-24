/*
 * RightTableTransactionScanner.cpp
 *
 *  Created on: 2020/12/19
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableBufferedTransactionScanner.h"

#include "scan_select/scan_planner/scanner/join/AbstractJoinCandidate.h"

namespace codablecash {

RightTableBufferedTransactionScanner::RightTableBufferedTransactionScanner(
		ScanResultMetadata* metadata, CdbTransaction* trx,
		const CdbTable* table, AbstractJoinCandidate* joinCandidate) : AbstractTransactionScanner(metadata, trx, table) {
	this->joinCandidate = joinCandidate->copy();
}

RightTableBufferedTransactionScanner::~RightTableBufferedTransactionScanner() {
	delete this->joinCandidate;
}

void RightTableBufferedTransactionScanner::start() {
}

void RightTableBufferedTransactionScanner::reset(const AbstractCdbKey* key) {
}

bool RightTableBufferedTransactionScanner::hasNext() {
	return false;
}

const CdbRecord* RightTableBufferedTransactionScanner::next() {
	return nullptr;
}

void RightTableBufferedTransactionScanner::shutdown() {
}

} /* namespace codablecash */
