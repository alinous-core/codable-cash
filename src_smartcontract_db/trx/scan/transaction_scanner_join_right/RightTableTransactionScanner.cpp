/*
 * RightTableTransactionScanner.cpp
 *
 *  Created on: 2020/12/19
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableTransactionScanner.h"

namespace codablecash {

RightTableTransactionScanner::RightTableTransactionScanner(CdbTransaction* trx, const CdbTable* table)
			: AbstractTransactionScanner(trx, table) {

}

RightTableTransactionScanner::~RightTableTransactionScanner() {

}

} /* namespace codablecash */
