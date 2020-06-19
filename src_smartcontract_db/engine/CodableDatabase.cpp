/*
 * CodableDatabase.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "transaction/CdbTransactionManager.h"
#include "transaction/SchemaObjectIdPublisher.h"
#include "transaction/CdbTransaction.h"

#include "base_io/File.h"

#include "schema/SchemaManager.h"

#include "table_store/CdbStorageManager.h"


namespace codablecash {

CodableDatabase::CodableDatabase() {
	this->trxManager = new CdbTransactionManager(this);
	this->schema = nullptr;
	this->loadedFile = nullptr;
	this->store = nullptr;
}

CodableDatabase::~CodableDatabase() {
	closeDatabase();

	delete this->trxManager;
	delete this->schema;
	delete this->store;
}

void CodableDatabase::createDatabase(File* dbdir) {
	dbdir->deleteDir();

	dbdir->mkdirs();

	// schema
	SchemaManager::createSchema(&SchemaManager::PUBLIC, dbdir);
}

bool CodableDatabase::loadDatabase(const File* dbdir) {
	if(!dbdir->exists() || !dbdir->isDirectory()){
		return false;
	}

	this->store = new CdbStorageManager();

	this->schema = new SchemaManager();
	this->schema->addSchemaUpdateListner(this->trxManager);
	this->schema->addSchemaUpdateListner(this->store);

	this->schema->loadSchema(dbdir);


	this->loadedFile = new File(*dbdir);

	return true;
}
void CodableDatabase::closeDatabase() noexcept {
	if(this->loadedFile != nullptr){
		delete this->loadedFile;
		this->loadedFile = nullptr;
	}
}

CdbTransaction* CodableDatabase::newTransaction() {
	checkDatabaseLoaded();

	uint64_t transactionId = this->schema->newTransactionId();

	return this->trxManager->newTransaction(transactionId);
}

CdbStorageManager* CodableDatabase::getStorageManager() const noexcept {
	return this->store;
}

SchemaManager* CodableDatabase::getSchemaManager() const noexcept {
	return this->schema;
}

uint64_t CodableDatabase::getSchemaObjectVersionId() const noexcept {
	SchemaObjectIdPublisher* schemaIdPublisher = this->trxManager->getSchemaObjectIdPublisher();

	return schemaIdPublisher->getSchemaObjectVersionId();
}

void CodableDatabase::checkDatabaseLoaded() const {
	if(this->loadedFile == nullptr){
		throw new CdbException(__FILE__, __LINE__);
	}
}

/*Schema* CodableDatabase::getSchema() const noexcept {
	return this->schema;
}*/

} /* namespace alinous */
