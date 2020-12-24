/*
 * RightTableTransactionScanner.cpp
 *
 *  Created on: 2020/12/19
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableBufferedTransactionScanner.h"

namespace codablecash {

RightTableBufferedTransactionScanner::RightTableBufferedTransactionScanner(
		ScanResultMetadata* metadata, CdbTransaction* trx,
		const CdbTable* table, AbstractJoinCandidate* joinCandidate) : AbstractTransactionScanner(metadata, trx, table) {
}

RightTableBufferedTransactionScanner::~RightTableBufferedTransactionScanner() {

}

void RightTableBufferedTransactionScanner::start() {
}

void RightTableBufferedTransactionScanner::reset(const AbstractCdbKey* key) {
}

bool RightTableBufferedTransactionScanner::hasNext() {
}

const CdbRecord* RightTableBufferedTransactionScanner::next() {
}

void RightTableBufferedTransactionScanner::shutdown() {
}

} /* namespace codablecash */
