/*
 * RightTableIndexTransactionScanner.cpp
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner_join_right/RightTableIndexTransactionScanner.h"

namespace codablecash {

RightTableIndexTransactionScanner::RightTableIndexTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table)
			: AbstractTransactionScanner(metadata, trx, table){
	// TODO Auto-generated constructor stub

}

RightTableIndexTransactionScanner::~RightTableIndexTransactionScanner() {
	// TODO Auto-generated destructor stub
}

} /* namespace codablecash */
