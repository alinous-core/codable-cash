/*
 * IndexStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/IndexStore.h"

#include "table/CdbTable.h"
#include "table/CdbTableIndex.h"
#include "table/CdbTableColumn.h"

#include "base/StackRelease.h"

#include "base_io/File.h"

#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

#include "table_store/CdbStorageManager.h"

#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbDataFactory.h"
#include "table_record/CdbRecord.h"

#include "table_record_key/CdbRecordKey.h"
#include "table_record_key/AbstractCdbKey.h"

#include "scan/IndexScanner.h"

#include "table_record_value/CdbOidValueList.h"

#include "engine/CdbOid.h"

using alinous::File;

namespace codablecash {

IndexStore::IndexStore(DiskCacheManager* cacheManager, const File* tableDir, const CdbTable* table, const CdbTableIndex* index) {
	this->tableDir = new File(*tableDir);
	this->table = table;
	this->index = index;
	this->btree = nullptr;
	this->opened = false;
	this->cacheManager = cacheManager;
}

IndexStore::~IndexStore() {
	close();

	delete this->tableDir;
	this->table = nullptr;
	this->index = nullptr;
	this->cacheManager = nullptr;
}

void IndexStore::createStore(const File* tableDir, const CdbTable* table, const CdbTableIndex* index, DiskCacheManager* cacheManager) {
	const UnicodeString* name = index->getName();

	Btree btree(tableDir, name, cacheManager, CdbStorageManager::keyFactory.copy(), CdbStorageManager::dataFactory.copy());

	BtreeConfig config;
	btree.create(&config);
}

void IndexStore::cleanupStore(const File* tableDir, const CdbTable* table, const CdbTableIndex* index) {
	const UnicodeString* name = index->getName();

	File* dir = tableDir->get(name); __STP(dir);
	dir->deleteDir();
}

void IndexStore::reset() {
	close();

	cleanupStore(this->tableDir, this->table, this->index);
	createStore(this->tableDir, this->table, this->index, this->cacheManager);

	load();
}


void IndexStore::load() {
	const UnicodeString* name = this->index->getName();
	this->btree = new Btree(this->tableDir, name, this->cacheManager, CdbStorageManager::keyFactory.copy(), CdbStorageManager::dataFactory.copy());

	BtreeOpenConfig opconf;
	this->btree->open(&opconf);
	this->opened = true;
}

void IndexStore::close() noexcept {
	if(this->btree != nullptr){
		if(this->opened){
			this->opened = false;
			this->btree->close();
		}

		delete this->btree;
		this->btree = nullptr;
	}
}

const CdbOid* IndexStore::getIndexOid() const noexcept {
	return this->index->getOid();
}

void IndexStore::insert(const CdbRecord* rec) {
	CdbRecordKey* key = new CdbRecordKey(); __STP(key);

	const ArrayList<CdbTableColumn>* list = this->index->getColumns();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = list->get(i);
		int pos = col->getPosition();
		const AbstractCdbValue* value = rec->get(pos);

		key->addKey(value->toKey());
	}


	CdbOidValueList* oidList = nullptr;
	IBlockObject* record = this->btree->findByKey(key);
	if(record != nullptr){
		oidList = dynamic_cast<CdbOidValueList*>(record);
		assert(oidList != nullptr);
	}
	else{
		oidList = new CdbOidValueList();
	}

	StackRelease<CdbOidValueList> __oidListRelease(oidList);
//	uint64_t newOid = rec->getOid()->getOidValue();

	oidList->addOid(rec->getOid()->copy());

	this->btree->putData(key, oidList);
}

IndexScanner* IndexStore::getScanner(CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	return new IndexScanner(begin, beginEq, end, endEq, this);
}

Btree* IndexStore::getBtree() const noexcept {
	return this->btree;
}

} /* namespace codablecash */
