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
}

CodableDatabase::~CodableDatabase() {
	delete this->trxManager;

}

void CodableDatabase::createDatabase(File* dbdir) {
	dbdir->deleteDir();

	dbdir->mkdirs();

	// schema
	Schema::createSchema(&Schema::PUBLIC, dbdir);
}

} /* namespace alinous */
