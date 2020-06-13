/*
 * AbstractTransactionScanner.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "transaction_scanner/AbstractTransactionScanner.h"

#include "transaction/CdbTransaction.h"

namespace codablecash {

AbstractTransactionScanner::AbstractTransactionScanner(CdbTransaction* trx) {
	this->trx = trx;
	this->trx->getUpdateCache();
}

AbstractTransactionScanner::~AbstractTransactionScanner() {
	this->trx = nullptr;
}

bool AbstractTransactionScanner::hasInsertedRecord() const noexcept {
}

} /* namespace codablecash */
