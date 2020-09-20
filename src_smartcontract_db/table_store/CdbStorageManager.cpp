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

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"

namespace codablecash {

CdbKeyFactory CdbStorageManager::keyFactory;
CdbDataFactory CdbStorageManager::dataFactory;

CdbStorageManager::CdbStorageManager() {
	this->schemaManager = nullptr;
	this->cacheManager = new DiskCacheManager();
	this->tableStoreMap = new HashMap<CdbOid, TableStore>();
}

CdbStorageManager::~CdbStorageManager() {
	this->schemaManager = nullptr;

	Iterator<CdbOid> *it = this->tableStoreMap->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		TableStore* tableStore = this->tableStoreMap->get(oid);

		delete tableStore;
	}

	delete this->tableStoreMap;
	delete this->cacheManager;
}

void CdbStorageManager::schemaLoaded(SchemaManager* sc) {
	this->schemaManager = sc;
}

void CdbStorageManager::onCreateTable(SchemaManager* mgr, const CdbTable* table) {
	const File* baseDir = mgr->getDatabaseBaseDir();

	TableStore* store = new TableStore(this->cacheManager, baseDir, table);
	store->createTable();
	store->loadTable();

	this->tableStoreMap->put(store->getOid(), store);
}

void CdbStorageManager::onAlterModify(SchemaManager* mgr, const CdbTable* table, const ColumnModifyContext* ctx) {


	// TODO : onAlterModify()
}

TableStore* CdbStorageManager::getTableStore(const CdbOid* oid) noexcept {
	return this->tableStoreMap->get(oid);
}

} /* namespace codablecash */
