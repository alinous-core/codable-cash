/*
 * RecordStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/RecordStore.h"
#include "table_store/CdbStorageManager.h"

#include "table/CdbTable.h"

#include "base_io/File.h"

#include "random_access_file/DiskCacheManager.h"

#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbRecord.h"

#include "table_record_key/CdbLongKey.h"

#include "engine/CdbOid.h"


namespace codablecash {

RecordStore::RecordStore(DiskCacheManager* cacheManager, const File* tableDir, const CdbTable* table) {
	this->tableDir = new File(*tableDir);
	this->table = table;
	this->cacheManager = cacheManager;
	this->btree = nullptr;
	this->opened = false;
}

RecordStore::~RecordStore() {
	close();

	delete this->tableDir;
	this->table =nullptr;
	this->cacheManager = nullptr;
}

void RecordStore::createStore(const File* tableDir, const CdbTable* table, DiskCacheManager* cacheManager) {
	const UnicodeString* name = table->getName();

	Btree btree(tableDir, name, cacheManager, CdbStorageManager::keyFactory.copy(), CdbStorageManager::dataFactory.copy());

	BtreeConfig config;
	btree.create(&config);

}

void RecordStore::load() {
	const UnicodeString* name = this->table->getName();
	this->btree = new Btree(this->tableDir, name, this->cacheManager, CdbStorageManager::keyFactory.copy(), CdbStorageManager::dataFactory.copy());

	BtreeOpenConfig opconf;
	this->btree->open(&opconf);
	this->opened = true;
}

void RecordStore::close() noexcept {
	if(this->btree != nullptr){
		if(this->opened){
			this->opened = false;
			this->btree->close();
		}

		delete this->btree;
		this->btree = nullptr;
	}
}

void RecordStore::insert(const CdbRecord* rec) {
	//CdbLongKey key(rec->getOid()); FIXME oid
	AbstractCdbKey* key = rec->getOid()->toKey(); __STP(key);

	this->btree->putData(key, rec);
}

} /* namespace codablecash */
