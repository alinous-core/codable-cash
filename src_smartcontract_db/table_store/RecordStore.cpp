/*
 * RecordStore.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "table_store/RecordStore.h"
#include "table/CdbTable.h"

#include "base_io/File.h"


namespace codablecash {

RecordStore::RecordStore(const File* tableDir, const CdbTable* table) {
	this->tableDir = new File(*tableDir);
	this->table = table;
}

RecordStore::~RecordStore() {
	delete this->tableDir;
	this->table =nullptr;
}

void RecordStore::createStore(const File* tableDir, const CdbTable* table) {

}

void RecordStore::load() {

}

} /* namespace codablecash */
