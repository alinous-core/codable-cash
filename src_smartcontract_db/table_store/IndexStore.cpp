/*
 * IndexStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/IndexStore.h"

#include "table/CdbTable.h"
#include "table/CdbTableIndex.h"

#include "base_io/File.h"

#include "btree/Btree.h"
#include "btree/BtreeConfig.h"

#include "table_store/CdbStorageManager.h"

#include "table_record/CdbKeyFactory.h"
#include "table_record/CdbDataFactory.h"


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

} /* namespace codablecash */
