/*
 * TableStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"
#include "table_store/IndexStore.h"

#include "base_io/File.h"

#include "table/CdbTable.h"

#include "schema/Schema.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "engine/CdbOid.h"
#include "engine/CdbException.h"

#include "table_record_value/AbstractCdbValue.h"
#include "table_record/CdbRecord.h"


namespace codablecash {

TableStore::TableStore(DiskCacheManager* cacheManager, const File* baseDir, const CdbTable* table) {
	this->baseDir = new File(*baseDir);
	this->table = table;

	this->recordStore = nullptr;
	this->indexStores = new HashMap<CdbOid, IndexStore>();

	this->cacheManager = cacheManager;
}

TableStore::~TableStore() {
	delete this->baseDir;

	delete this->recordStore;
	this->table = nullptr;

	Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		IndexStore* store = this->indexStores->get(oid);

		delete store;
	}
	delete this->indexStores;

	this->cacheManager = nullptr;
}

const CdbOid* TableStore::getOid() const noexcept {
	return this->table->getOid();
}

void TableStore::createTable() {
	const Schema* schema = this->table->getSchema();
	const UnicodeString* schemaName = schema->getName();
	const UnicodeString* tableName = this->table->getName();

	File* schemaDir = this->baseDir->get(schemaName); __STP(schemaDir);
	File* tableDir = schemaDir->get(tableName); __STP(tableDir);

	tableDir->deleteDir();
	tableDir->mkdirs();

	RecordStore::createStore(tableDir, this->table, this->cacheManager);

	const ArrayList<CdbTableIndex>* list = this->table->getIndexes();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbTableIndex* index = list->get(i);

		IndexStore::createStore(tableDir, this->table, index, this->cacheManager);
	}
}

void TableStore::loadTable() {
	const Schema* schema = this->table->getSchema();
	const UnicodeString* schemaName = schema->getName();
	const UnicodeString* tableName = this->table->getName();

	File* schemaDir = this->baseDir->get(schemaName); __STP(schemaDir);
	File* tableDir = schemaDir->get(tableName); __STP(tableDir);

	this->recordStore = new RecordStore(this->cacheManager ,tableDir, this->table);

	const ArrayList<CdbTableIndex>* list = this->table->getIndexes();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbTableIndex* index = list->get(i);

		IndexStore* store = new IndexStore(this->cacheManager, tableDir, this->table, index);
		this->indexStores->put(store->getIndexOid(), store);
	}

	// load
	this->recordStore->load();

	Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		IndexStore* store = this->indexStores->get(oid);
		store->load();
	}
}

void TableStore::insert(CdbRecord* rec) {

}

void TableStore::validateRecord(CdbRecord* rec) {
	const ArrayList<CdbTableColumn>* metaData = this->table->getColumns();
	const ArrayList<AbstractCdbValue>* values = rec->getValues();

	int metaSize = metaData->size();
	int valueSize = values->size();

	if(metaSize != valueSize){
		throw new CdbException(L"Record's column size is wrong", __FILE__, __LINE__);
	}


}

} /* namespace codablecash */
