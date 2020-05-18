/*
 * CdbStorageManager.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"

#include "schema/SchemaManager.h"

#include "random_access_file/DiskCacheManager.h"

#include "base/UnicodeString.h"

#include "table/CdbTable.h"

#include "engine/CdbOid.h"

namespace codablecash {

CdbStorageManager::CdbStorageManager() {
	this->schemaManager = nullptr;
	this->cacheManager = new DiskCacheManager();
	this->tableStoreMap = new HashMap<CdbOid, TableStore>();
}

CdbStorageManager::~CdbStorageManager() {
	this->schemaManager = nullptr;
	delete this->cacheManager;

	delete this->tableStoreMap;
}

void CdbStorageManager::schemaLoaded(SchemaManager* sc) {
	this->schemaManager = sc;
}

void CdbStorageManager::onCreateTable(SchemaManager* mgr, CdbTable* table) {
	const Schema* schema = table->getSchema();
	const File* baseDir = mgr->getDatabaseBaseDir();

	// FIXME create storage
}


} /* namespace codablecash */
