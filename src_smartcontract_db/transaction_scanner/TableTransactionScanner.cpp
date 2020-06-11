/*
 * TableTransactionScan.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "transaction_scanner/TableTransactionScanner.h"

#include "transaction/CdbTransaction.h"

namespace codablecash {

TableTransactionScanner::TableTransactionScanner(CdbTransaction* trx, TableStore* tableStore)
	: AbstractTransactionScanner(trx) {
	this->tableStore = tableStore;
}

TableTransactionScanner::~TableTransactionScanner() {
	this->tableStore = nullptr;
}

} /* namespace codablecash */
