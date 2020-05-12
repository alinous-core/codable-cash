/*
 * CodableDatabase.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "engine/CodableDatabase.h"

#include "transaction/CdbTransactionManager.h"

#include "base_io/File.h"

#include "schema/Schema.h"

#include "transaction/CdbTransaction.h"

namespace codablecash {

CodableDatabase::CodableDatabase() {
	this->trxManager = new CdbTransactionManager(this);
	this->schema = nullptr;
	this->loadedFile = nullptr;
}

CodableDatabase::~CodableDatabase() {
	closeDatabase();

	delete this->trxManager;
	delete this->schema;
}

void CodableDatabase::createDatabase(File* dbdir) {
	dbdir->deleteDir();

	dbdir->mkdirs();

	// schema
	Schema::createSchema(&Schema::PUBLIC, dbdir);
}

bool CodableDatabase::loadDatabase(const File* dbdir) {
	if(!dbdir->exists() || !dbdir->isDirectory()){
		return false;
	}

	this->schema = new Schema();
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
	return this->trxManager->newTransaction();
}

} /* namespace alinous */

