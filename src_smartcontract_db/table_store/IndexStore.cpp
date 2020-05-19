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


namespace codablecash {

IndexStore::IndexStore(const File* tableDir, const CdbTable* table, const CdbTableIndex* index) {
	this->tableDir = new File(*tableDir);
	this->table = table;
	this->index = index;
}

IndexStore::~IndexStore() {
	delete this->tableDir;
	this->table = nullptr;
	this->index = nullptr;
}

void IndexStore::load() {
}

const CdbOid* IndexStore::getIndexOid() const noexcept {
	return this->index->getOid();
}

} /* namespace codablecash */
