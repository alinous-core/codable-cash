/*
 * CdbTransaction.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "transaction/CdbTransaction.h"
#include "transaction/CdbTransactionManager.h"


namespace codablecash {

CdbTransaction::CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId) {
	this->trxManager = trxManager;
	this->transactionId = transactionId;
}

CdbTransaction::~CdbTransaction() {
	this->trxManager = nullptr;
}

void CdbTransaction::commit() {

}
/*
void CdbTransaction::rollback() {

}
*/

void CdbTransaction::createTable(CreateTableLog* cmd) {
	commit();
}

} /* namespace codablecash */
