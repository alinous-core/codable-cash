/*
 * RecordScanner.cpp
 *
 *  Created on: 2020/06/11
 *      Author: iizuka
 */

#include "scan_select/scan/RecordScanner.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "schema_table/table_store/TableStore.h"
#include "schema_table/table_store/RecordStore.h"

#include "schema_table/record/table_record/CdbRecord.h"

using namespace alinous;

namespace codablecash {

RecordScanner::RecordScanner(TableStore* tableStore) {
	this->tableStore = tableStore;
	this->scanner = nullptr;
}

RecordScanner::~RecordScanner() {
	shutdown();
	this->tableStore = nullptr;
}

void RecordScanner::start() {
	RecordStore* recStore = this->tableStore->getRecordStore();

	Btree* btree = recStore->getBtree();

	this->scanner = btree->getScanner();
	this->scanner->begin();
}

void RecordScanner::shutdown() noexcept {
	if(this->scanner != nullptr){
		delete this->scanner;
		this->scanner = nullptr;
	}
}

bool RecordScanner::hasNext() {
	return this->scanner->hasNext();

}

const CdbRecord* RecordScanner::next() {
	const IBlockObject* obj = this->scanner->next();
	return dynamic_cast<const CdbRecord*>(obj);
}

} /* namespace codablecash */
