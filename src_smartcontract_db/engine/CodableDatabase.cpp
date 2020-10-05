/*
 * CodableDatabase.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"
#include "engine/CdbLocalCacheManager.h"

#include "transaction/CdbTransactionManager.h"
#include "transaction/SchemaObjectIdPublisher.h"
#include "transaction/CdbTransaction.h"

#include "base_io/File.h"

#include "schema/SchemaManager.h"

#include "table_store/CdbStorageManager.h"

#include "engine_lock/DatabaseLevelLock.h"

#include "base/StackRelease.h"

#include "table_record_local/LocalOidFactory.h"

namespace codablecash {

CodableDatabase::CodableDatabase() {
	this->trxManager = new CdbTransactionManager(this);
	this->schema = nullptr;
	this->loadedFile = nullptr;
	this->store = nullptr;
	this->dbLevelLock = new DatabaseLevelLock();
	this->localCacheManager = nullptr;
	this->localOidFactory = nullptr;
}

CodableDatabase::~CodableDatabase() {
	closeDatabase();

	delete this->trxManager;
	this->trxManager = nullptr;

	delete this->dbLevelLock;
	this->dbLevelLock = nullptr;
}

void CodableDatabase::createDatabase(File* dbdir) {
	dbdir->deleteDir();

	dbdir->mkdirs();

	// schema
	SchemaManager::createSchema(&SchemaManager::PUBLIC, dbdir);
}

bool CodableDatabase::loadDatabase(const File* dbdir) {
	File* tmpdir = dbdir->get(L"temp"); __STP(tmpdir);
	return loadDatabase(dbdir, tmpdir);
}

bool CodableDatabase::loadDatabase(const File* dbdir, const File* tmpdir) {
	if(!dbdir->exists() || !dbdir->isDirectory()){
		return false;
	}

	if(!tmpdir->exists()){
		tmpdir->mkdirs();
	}

	this->localOidFactory = new LocalOidFactory();
	this->localCacheManager = new CdbLocalCacheManager(tmpdir, this->localOidFactory);
	this->localCacheManager->init();

	this->store = new CdbStorageManager();

	this->schema = new SchemaManager(this);
	this->schema->addSchemaUpdateListner(this->trxManager);
	this->schema->addSchemaUpdateListner(this->store);

	try{
		this->schema->loadSchema(dbdir);
	}
	catch(Exception* e){
		delete e;
		return false;
	}

	this->loadedFile = new File(*dbdir);

	return true;
}

void CodableDatabase::closeDatabase() noexcept {
	if(this->loadedFile != nullptr || this->schema != nullptr){
		delete this->store;
		this->store = nullptr;

		delete this->schema;
		this->schema = nullptr;

		delete this->loadedFile;
		this->loadedFile = nullptr;

		delete this->localCacheManager;
		this->localCacheManager = nullptr;

		delete this->localOidFactory;
		this->localOidFactory = nullptr;
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

ReadLockHandle* CodableDatabase::databaseReadLock() {
	return this->dbLevelLock->readLock();
}

WriteLockHandle* CodableDatabase::databaseWriteLock() {
	return this->dbLevelLock->writeLock();
}

} /* namespace alinous */
