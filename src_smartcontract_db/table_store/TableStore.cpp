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

#include "engine_lock/TableLevelLock.h"
#include "engine_lock/AbstractLockHandle.h"
#include "engine_lock/WriteLockHandle.h"
#include "engine_lock/ReadLockHandle.h"
#include "engine_lock/AbstractLockHandle.h"
#include "engine_lock/AbstractDatabaseLock.h"

#include "table/CdbTableIndex.h"
#include "table/CdbTableColumn.h"

#include "table_record/CdbRecord.h"

#include "table_record_value/AbstractCdbValue.h"

#include "table_record_key/CdbLongKey.h"

#include "table_store/RecordValueConverter.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "schema_alter_ctx/ColumnModifyContext.h"


namespace codablecash {

TableStore::TableStore(DiskCacheManager* cacheManager, const File* baseDir, const CdbTable* table) {
	this->baseDir = new File(*baseDir);
	this->table = table;

	this->recordStore = nullptr;
	this->indexStores = new HashMap<CdbOid, IndexStore>();

	this->cacheManager = cacheManager;
	this->tableLock = new TableLevelLock();
}

TableStore::~TableStore() {
	closeTable();

	delete this->baseDir;
	this->table = nullptr;

	delete this->indexStores;

	this->cacheManager = nullptr;
	delete this->tableLock;
}

void TableStore::closeTable() {
	if(this->recordStore != nullptr){
		this->recordStore->close();
		delete this->recordStore;
		this->recordStore = nullptr;

		Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
		while(it->hasNext()){
			const CdbOid* oid = it->next();
			IndexStore* store = this->indexStores->get(oid);

			delete store;
		}
		this->indexStores->clear();
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

const CdbOid* TableStore::getOid() const noexcept {
	return this->table->getOid();
}

const CdbTable* TableStore::getTable() const noexcept {
	return this->table;
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

void TableStore::addNewIndex(const CdbTableIndex* index) {
	const Schema* sc = this->table->getSchema();
	const UnicodeString* schemaName = sc->getName();

	const UnicodeString* tableName = table->getName();

	File* schemaDir = this->baseDir->get(schemaName); __STP(schemaDir);
	File* tableDir = schemaDir->get(tableName); __STP(tableDir);
	IndexStore::createStore(tableDir, this->table, index, this->cacheManager);

	IndexStore* indexstore = new IndexStore(this->cacheManager, tableDir, this->table, index);
	indexstore->load();

	this->indexStores->put(indexstore->getIndexOid(), indexstore);
}

void TableStore::removeIndex(const CdbTableIndex* index) {
	const CdbOid* indexOid = index->getOid();
	IndexStore* indexStore = getIndexStore(indexOid); __STP(indexStore);

	indexStore->close();
	this->indexStores->remove(indexOid);

	const Schema* sc = this->table->getSchema();
	const UnicodeString* schemaName = sc->getName();

	File* schemaDir = this->baseDir->get(schemaName); __STP(schemaDir);

	const UnicodeString* tableName = table->getName();
	File* tableDir = schemaDir->get(tableName); __STP(tableDir);

	IndexStore::cleanupStore(tableDir, this->table, index);
}

void TableStore::resetAllIndexes() {
	Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		IndexStore* store = this->indexStores->get(oid);

		store->reset();
	}
}

void TableStore::modifyRecords(const ColumnModifyContext* ctx) {
	CdbTableColumn* column = ctx->getColumn();
	const AbstractCdbValue* defaultValue = ctx->getDefaultValue();

	RecordValueConverter converter(column, defaultValue);

	Btree* btree = this->recordStore->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();

	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		const CdbRecord* record = dynamic_cast<const CdbRecord*>(obj);

		// convert value
		CdbRecord* newRecord = converter.processUpdate(record); __STP(newRecord);
		this->recordStore->insert(newRecord);
	}
}

void TableStore::buildAllIndexes() {
	ArrayList<IndexStore> list;
	Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		IndexStore* store = this->indexStores->get(oid);

		list.addElement(store);
	}

	Btree* btree = this->recordStore->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();

	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		const CdbRecord* record = dynamic_cast<const CdbRecord*>(obj);

		addRecord2Index(&list, record);
	}
}

void TableStore::addRecord2Index(const ArrayList<IndexStore>* indexStoreList, const CdbRecord* rec) {
	int maxLoop = indexStoreList->size();
	for(int i = 0; i != maxLoop; ++i){
		IndexStore* store = indexStoreList->get(i);

		store->insert(rec);
	}
}

void TableStore::buildIndex(CdbTableIndex* index) {
	const CdbOid* indexOid = index->getOid();
	IndexStore* store = getIndexStore(indexOid);

	Btree* btree = this->recordStore->getBtree();
	BtreeScanner* scanner = btree->getScanner(); __STP(scanner);

	scanner->begin();

	while(scanner->hasNext()){
		const IBlockObject* obj = scanner->next();
		const CdbRecord* record = dynamic_cast<const CdbRecord*>(obj);

		store->insert(record);
	}
}

void TableStore::insert(const CdbRecord* rec) {
	this->recordStore->insert(rec);

	addToIndexes(rec);
}

void TableStore::addToIndexes(const CdbRecord* rec) {
	Iterator<CdbOid>* it = this->indexStores->keySet()->iterator(); __STP(it);
	while(it->hasNext()){
		const CdbOid* oid = it->next();
		IndexStore* store = this->indexStores->get(oid);

		store->insert(rec);
	}
}

void TableStore::onRename(const TableRenameContext* ctx) {
	closeTable();

	// TODO onRename

	loadTable();
}


void TableStore::validateRecord(CdbRecord* rec) {
	const ArrayList<CdbTableColumn>* metaData = this->table->getColumns();
	const ArrayList<AbstractCdbValue>* values = rec->getValues();

	int metaSize = metaData->size();
	int valueSize = values->size();

	if(metaSize != valueSize){
		throw new CdbException(L"Record's column size is wrong", __FILE__, __LINE__);
	}

	for(int i = 0; i != metaSize; ++i){
		CdbTableColumn* meta = metaData->get(i);
		AbstractCdbValue* value = values->get(i);

		validateRecordColumnValue(meta, value);
	}

}

void TableStore::validateRecordColumnValue(CdbTableColumn* meta, AbstractCdbValue* value) {


}

IndexStore* TableStore::getIndexStore(const CdbOid* indexoid) const noexcept {
	return this->indexStores->get(indexoid);
}

CdbRecord* TableStore::findRecord(const CdbOid* recordOid) {
	AbstractCdbKey* key = recordOid->toKey(); __STP(key);

	Btree* btree = this->recordStore->getBtree();

	IBlockObject* obj = btree->findByKey(key);
	if(obj == nullptr){
		return nullptr;
	}

	CdbRecord* record = dynamic_cast<CdbRecord*>(obj);
	assert(record != nullptr);

	return record;
}

AbstractLockHandle* TableStore::writeLock() {
	return this->tableLock->writeLock();
}

AbstractLockHandle* TableStore::readLock() {
	return this->tableLock->readLock();
}

} /* namespace codablecash */
