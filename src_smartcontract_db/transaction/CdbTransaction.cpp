/*
 * CdbTransaction.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "transaction/CdbTransaction.h"
#include "transaction/CdbTransactionManager.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"

#include "base/StackRelease.h"

#include "engine/CdbException.h"


namespace codablecash {

CdbTransaction::CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId) {
	this->trxManager = trxManager;
	this->transactionId = transactionId;
}

CdbTransaction::~CdbTransaction() {
	this->trxManager = nullptr;
	this->cmdList.deleteElements();
}

void CdbTransaction::commit() {
	while(!this->cmdList.isEmpty()){
		AbstractTransactionLog* cmd = nullptr;

		try{
			cmd = this->cmdList.remove(0);
			cmd->commit(this->trxManager);
		}
		catch(CdbException* e){
			e->setCmd(cmd);
			rollback();
			throw e;
		}
	}
}

void CdbTransaction::rollback() {
	this->cmdList.deleteElements();
	this->cmdList.reset();
}


void CdbTransaction::createTable(CreateTableLog* cmd) {
	commit();

	this->cmdList.addElement(cmd);
}

} /* namespace codablecash */
