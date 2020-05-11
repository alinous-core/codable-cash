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


namespace codablecash {

CodableDatabase::CodableDatabase() {
	this->trxManager = new CdbTransactionManager();
	this->schema = nullptr;
}

CodableDatabase::~CodableDatabase() {
	delete this->trxManager;
	delete this->schema;
}

void CodableDatabase::createDatabase(File* dbdir) {
	dbdir->deleteDir();

	dbdir->mkdirs();

	// schema
	Schema::createSchema(&Schema::PUBLIC, dbdir);
}

bool CodableDatabase::loadDatabase(File* dbdir) {
	if(!dbdir->exists() || !dbdir->isDirectory()){
		return false;
	}

	this->schema = new Schema();
	this->schema->loadSchema(dbdir);

	return true;
}

} /* namespace alinous */
