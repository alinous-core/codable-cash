/*
 * CdbTransactionManager.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "transaction/CdbTransactionManager.h"
#include "transaction/CdbTransaction.h"
#include "transaction/SchemaObjectIdPublisher.h"
#include "transaction/RecordObjectIdPublisher.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"

#include "table_record/CdbTableIdentifier.h"


namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
	this->schemaIdPublisher = nullptr;
	this->recordObjectIdPublisher = nullptr;
	this->schemaManager = nullptr;
	this->committedCommands = new ArrayList<AbstractTransactionLog>();
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
	delete this->schemaIdPublisher;
	this->schemaManager = nullptr;

	delete this->recordObjectIdPublisher;
	this->recordObjectIdPublisher = nullptr;

	this->committedCommands->deleteElements();
	delete this->committedCommands;
}

void CdbTransactionManager::schemaLoaded(SchemaManager* sc) {
	delete this->schemaIdPublisher;
	this->schemaIdPublisher = new SchemaObjectIdPublisher(sc);
	this->recordObjectIdPublisher = new RecordObjectIdPublisher(sc);

	this->schemaManager = sc;
}

void CdbTransactionManager::onCreateTable(SchemaManager* mgr, const CdbTable* table) {
	// do nothing
}


CdbTransaction* CdbTransactionManager::newTransaction(uint64_t transactionId) {
	CdbTransaction* trx = new CdbTransaction(this, transactionId);

	return trx;
}

SchemaObjectIdPublisher* CdbTransactionManager::getSchemaObjectIdPublisher() const noexcept {
	return this->schemaIdPublisher;
}

RecordObjectIdPublisher* CdbTransactionManager::getRecordObjectIdPublisher() const noexcept {
	return this->recordObjectIdPublisher;
}

void CdbTransactionManager::commitCreateTable(CreateTableLog* cmd) {
	CdbTable* table = cmd->getTable();
	this->schemaManager->createTable(table);

	this->committedCommands->addElement(cmd);
}

void CdbTransactionManager::commitInsert(InsertLog* cmd) {
	CdbTableIdentifier* tableIdentifier = cmd->getCdbTableIdentifier();
	const UnicodeString* schemaName = tableIdentifier->getSchema();
	const UnicodeString* tableName = tableIdentifier->getTable();

	Schema* schema = this->schemaManager->getSchema(schemaName);
	if(schema == nullptr){
		throw new CdbException(L"", __FILE__, __LINE__);
	}



	this->committedCommands->addElement(cmd);
}

} /* namespace codablecash */
