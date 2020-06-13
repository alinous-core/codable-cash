/*
 * RecordScanner.cpp
 *
 *  Created on: 2020/06/11
 *      Author: iizuka
 */

#include "scan/RecordScanner.h"

#include "btree/Btree.h"
#include "btree/BtreeScanner.h"

#include "table_store/TableStore.h"
#include "table_store/RecordStore.h"

#include "table_record/CdbRecord.h"

using namespace alinous;

namespace codablecash {

RecordScanner::RecordScanner(TableStore* tableStore) {
	this->tableStore = tableStore;
	this->scanner = nullptr;
}

RecordScanner::~RecordScanner() {
	this->tableStore = nullptr;
}

void RecordScanner::start() {
	RecordStore* recStore = this->tableStore->getRecordStore();

	Btree* btree = recStore->getBtree();
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
