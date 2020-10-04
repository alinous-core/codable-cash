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

#include "schema/ColumnModifyContext.h"
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

	const ArrayList<Schema>* sclist = this->schemaManager->getSchemaList();

	int maxLoop = sclist->size();
	for(int i = 0; i != maxLoop; ++i){
		Schema* schema = sclist->get(i);

		loadSchemaStore(schema);
	}

}

void CdbStorageManager::loadSchemaStore(Schema* schema) {

}

void CdbStorageManager::onCreateTable(SchemaManager* mgr, const CdbTable* table) {
	const File* baseDir = mgr->getDatabaseBaseDir();

	TableStore* store = new TableStore(this->cacheManager, baseDir, table);
	store->createTable();
	store->loadTable();

	this->tableStoreMap->put(store->getOid(), store);
}

void CdbStorageManager::onAlterModify(SchemaManager* mgr, const CdbTable* table, const ColumnModifyContext* ctx) {
	const CdbOid* tableOid = table->getOid();

	TableStore* store = getTableStore(tableOid);

	handleUniqueKeyOnAlterModify(store, ctx);

	ColumnModifyContext::NotNullChage notNullChange = ctx->getNotNullChange();
	CdbTableIndex* newIndex = ctx->getNewIndex();

	bool recordModified = false;
	if(ctx->isTypeChanged() || notNullChange == ColumnModifyContext::NotNullChage::TO_NOT_NULL){
		store->resetAllIndexes();
		store->modifyRecords(ctx);
		recordModified = true;
	}

	if(recordModified){
		store->buildAllIndexes();
	}
	else if(!recordModified && newIndex != nullptr){
		CdbTableIndex* newIndex = ctx->getNewIndex();
		store->buildIndex(newIndex);
	}

}

void CdbStorageManager::handleUniqueKeyOnAlterModify(TableStore* store,	const ColumnModifyContext* ctx) {
	CdbTableIndex* index = ctx->getNewIndex();
	if(index != nullptr){
		store->addIndex(index);
		return;
	}

	index = ctx->getRemovalIndex();
	if(index != nullptr){
		store->removeIndex(index);
	}
}

void CdbStorageManager::onDropPrimaryKey(SchemaManager* mgr, const CdbTable* table, const CdbTableIndex* primaryKey) {
	const CdbOid* tableOid = table->getOid();

	TableStore* store = getTableStore(tableOid);
	store->removeIndex(primaryKey);
}

TableStore* CdbStorageManager::getTableStore(const CdbOid* tableoid) noexcept {
	return this->tableStoreMap->get(tableoid);
}


} /* namespace codablecash */
