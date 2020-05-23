/*
 * RecordStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/RecordStore.h"
#include "table/CdbTable.h"

#include "base_io/File.h"

#include "random_access_file/DiskCacheManager.h"

namespace codablecash {

RecordStore::RecordStore(DiskCacheManager* cacheManager, const File* tableDir, const CdbTable* table) {
	this->tableDir = new File(*tableDir);
	this->table = table;
	this->cacheManager = cacheManager;
}

RecordStore::~RecordStore() {
	delete this->tableDir;
	this->table =nullptr;
	this->cacheManager = nullptr;
}

void RecordStore::createStore(const File* tableDir, const CdbTable* table) {
	// FIXME
}

void RecordStore::load() {

}

} /* namespace codablecash */
