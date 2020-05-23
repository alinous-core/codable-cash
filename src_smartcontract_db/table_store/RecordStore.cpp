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

#include "table_record/CdbDataFactory.h"
#include "table_record/CdbKeyFactory.h"


namespace codablecash {

RecordStore::RecordStore(DiskCacheManager* cacheManager, const File* tableDir, const CdbTable* table) {
	this->tableDir = new File(*tableDir);
	this->table = table;
	this->cacheManager = cacheManager;
	this->btree = nullptr;
}

RecordStore::~RecordStore() {
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

	// FIXME
}

void RecordStore::close() noexcept {
	if(this->btree != nullptr){
		this->btree->close();

		delete this->btree;
		this->btree = nullptr;
	}
}

} /* namespace codablecash */
