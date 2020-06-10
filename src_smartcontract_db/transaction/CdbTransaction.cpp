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
#include "transaction_log/InsertLog.h"

#include "base/StackRelease.h"

#include "engine/CdbException.h"

#include "table_record/CdbTableIdentifier.h"

#include "schema/Schema.h"

#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"

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

void CdbTransaction::insert(InsertLog* cmd) noexcept {
	this->cmdList.addElement(cmd);
}

TableTransactionScanner* CdbTransaction::getTableTransactionScanner(CdbTableIdentifier* tableId, AbstractScanCondition* condition) {
	const UnicodeString* schemaName = tableId->getSchema();
	const UnicodeString* tableName = tableId->getTable();

	Schema* schema = this->trxManager->getSchema(schemaName);
	CdbTable* table = schema->getCdbTableByName(tableName);

	const CdbOid* oid = table->getOid();
	CdbStorageManager* store = this->trxManager->getStorageManager();

	TableStore* tableStore = store->getTableStore(oid);

}

} /* namespace codablecash */
