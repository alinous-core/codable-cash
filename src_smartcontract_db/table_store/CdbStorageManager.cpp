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
#include "base/StackRelease.h"

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

	Iterator<CdbOid> *it = this->tableStoreMap->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		TableStore* tableStore = this->tableStoreMap->get(oid);

		delete tableStore;
	}

	delete this->tableStoreMap;
}

void CdbStorageManager::schemaLoaded(SchemaManager* sc) {
	this->schemaManager = sc;
}

void CdbStorageManager::onCreateTable(SchemaManager* mgr, const CdbTable* table) {
	const File* baseDir = mgr->getDatabaseBaseDir();

	TableStore* store = new TableStore(baseDir, table);
	store->createTable();
	store->loadTable();

	this->tableStoreMap->put(store->getOid(), store);
}


} /* namespace codablecash */
