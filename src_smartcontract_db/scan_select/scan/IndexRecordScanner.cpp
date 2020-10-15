/*
 * IndexRecordScanner.cpp
 *
 *  Created on: 2020/08/18
 *      Author: iizuka
 */

#include "scan_select/scan/IndexRecordScanner.h"
#include "scan_select/scan/IndexScanner.h"

#include "schema_table/table_store/TableStore.h"

#include "schema_table/record/table_record/CdbRecord.h"

namespace codablecash {

IndexRecordScanner::IndexRecordScanner(IndexScanner* indexScanner, TableStore* tableStore) {
	this->indexScanner = indexScanner;
	this->tableStore = tableStore;
	this->record = nullptr;
}

IndexRecordScanner::~IndexRecordScanner() {
	shutdown();
}

void IndexRecordScanner::start() {
	this->indexScanner->start();
}

void IndexRecordScanner::shutdown() noexcept {
	if(this->indexScanner != nullptr){
		this->indexScanner->shutdown();
		delete this->indexScanner;
		this->indexScanner = nullptr;

		this->tableStore = nullptr;

		delete this->record;
		this->record = nullptr;
	}
}

bool IndexRecordScanner::hasNext() {
	return this->indexScanner->hasNext();
}

const CdbRecord* IndexRecordScanner::next() {
	const CdbOid* recordOid = this->indexScanner->next();

	delete this->record;
	this->record = nullptr;
	this->record = this->tableStore->findRecord(recordOid);

	return record;
}

TableStore* IndexRecordScanner::getTableStore() const noexcept {
	return this->tableStore;
}

} /* namespace codablecash */
