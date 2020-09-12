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
#include "schema/Schema.h"

#include "table_record/CdbTableIdentifier.h"

#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"


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
		throw new CdbException(L"Schema to INSERT TABLE does not exists.", __FILE__, __LINE__);
	}

	CdbTable* table = schema->getCdbTableByName(tableName);
	const CdbOid* oid = table->getOid();

	CdbStorageManager* storeManager = this->db->getStorageManager();
	TableStore* store = storeManager->getTableStore(oid);

	assert(store != nullptr);

	const ArrayList<CdbRecord>* records = cmd->getRecords();

	int maxLoop = records->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* rec = records->get(i);
		store->validateRecord(rec);
	}


	for(int i = 0; i != maxLoop; ++i){
		CdbRecord* rec = records->get(i);

		store->insert(rec);
	}

	this->committedCommands->addElement(cmd);
}

Schema* CdbTransactionManager::getSchema(const UnicodeString* name) const noexcept {
	return this->schemaManager->getSchema(name);
}

CdbStorageManager* CdbTransactionManager::getStorageManager() const noexcept {
	return this->db->getStorageManager();
}

ReadLockHandle* CdbTransactionManager::databaseReadLock() {
	return this->db->databaseReadLock();
}

WriteLockHandle* CdbTransactionManager::databaseWriteLock() {
	return this->db->databaseWriteLock();
}


} /* namespace codablecash */
