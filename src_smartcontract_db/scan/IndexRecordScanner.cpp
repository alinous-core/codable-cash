/*
 * IndexRecordScanner.cpp
 *
 *  Created on: 2020/08/18
 *      Author: iizuka
 */

#include "scan/IndexRecordScanner.h"
#include "scan/IndexScanner.h"

#include "table_store/TableStore.h"

namespace codablecash {

IndexRecordScanner::IndexRecordScanner(IndexScanner* indexScanner, TableStore* tableStore) {
	this->indexScanner = indexScanner;
	this->tableStore = tableStore;
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
		this->indexScanner = nullptr;

		this->tableStore = nullptr;
	}
}

bool IndexRecordScanner::hasNext() {
	return this->indexScanner->hasNext();
}

const CdbRecord* IndexRecordScanner::next() {
	const CdbOid* recordOid = this->indexScanner->next();


}

} /* namespace codablecash */
