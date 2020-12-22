/*
 * RightTableOrTransactionScanner.cpp
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableOrTransactionScanner.h"

namespace codablecash {

RightTableOrTransactionScanner::RightTableOrTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table)
		: AbstractTransactionScanner(metadata, trx, table){
	// TODO Auto-generated constructor stub

}

RightTableOrTransactionScanner::~RightTableOrTransactionScanner() {
	// TODO Auto-generated destructor stub
}

} /* namespace codablecash */
