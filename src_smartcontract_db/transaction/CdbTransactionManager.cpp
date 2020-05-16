/*
 * CdbTransactionManager.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "transaction/CdbTransactionManager.h"
#include "transaction/CdbTransaction.h"
#include "transaction/SchemaObjectIdPublisher.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"

#include "engine/CodableDatabase.h"


namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
	this->schemaIdPublisher = nullptr;
	this->schema = nullptr;
	this->committedCommands = new ArrayList<AbstractTransactionLog>();
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
	delete this->schemaIdPublisher;
	this->schema = nullptr;

	this->committedCommands->deleteElements();
	delete this->committedCommands;
}

void CdbTransactionManager::schemaLoaded(Schema* sc) {
	delete this->schemaIdPublisher;
	this->schemaIdPublisher = new SchemaObjectIdPublisher(sc);

	this->schema = sc;
}

CdbTransaction* CdbTransactionManager::newTransaction(uint64_t transactionId) {
	CdbTransaction* trx = new CdbTransaction(this, transactionId);

	return trx;
}

SchemaObjectIdPublisher* CdbTransactionManager::getSchemaObjectIdPublisher() const noexcept {
	return this->schemaIdPublisher;
}

void CdbTransactionManager::commitCreateTable(CreateTableLog* cmd) {

	this->committedCommands->addElement(cmd);
}

} /* namespace codablecash */
