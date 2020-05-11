/*
 * CdbTransaction.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "transaction/CdbTransaction.h"
#include "transaction/CdbTransactionManager.h"


namespace codablecash {

CdbTransaction::CdbTransaction(CdbTransactionManager* trxManager) {
	this->trxManager = trxManager;
}

CdbTransaction::~CdbTransaction() {
	this->trxManager = nullptr;
}

} /* namespace codablecash */
