/*
 * CdbTransactionManager.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "transaction/CdbTransactionManager.h"
#include "transaction/CdbTransaction.h"

#include "engine/CodableDatabase.h"

namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
}

CdbTransaction* CdbTransactionManager::newTransaction(uint64_t transactionId) {

	CdbTransaction* trx = new CdbTransaction(this, transactionId);

	return trx;
}

} /* namespace codablecash */
