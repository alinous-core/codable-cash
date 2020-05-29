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

#include "schema/SchemaManager.h"


namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
	this->schemaIdPublisher = nullptr;
	this->recordObjectIdPublisher = nullptr;
	this->schema = nullptr;
	this->committedCommands = new ArrayList<AbstractTransactionLog>();
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
	delete this->schemaIdPublisher;
	this->schema = nullptr;

	delete this->recordObjectIdPublisher;
	this->recordObjectIdPublisher = nullptr;

	this->committedCommands->deleteElements();
	delete this->committedCommands;
}

void CdbTransactionManager::schemaLoaded(SchemaManager* sc) {
	delete this->schemaIdPublisher;
	this->schemaIdPublisher = new SchemaObjectIdPublisher(sc);

	this->schema = sc;
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
	schema->createTable(table);

	this->committedCommands->addElement(cmd);
}

void CdbTransactionManager::commitInsert(InsertLog* cmd) {


	this->committedCommands->addElement(cmd);
}

} /* namespace codablecash */
