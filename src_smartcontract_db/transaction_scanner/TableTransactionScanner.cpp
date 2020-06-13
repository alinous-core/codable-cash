/*
 * TableTransactionScan.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "transaction_scanner/TableTransactionScanner.h"

#include "transaction/CdbTransaction.h"

#include "scan/RecordScanner.h"

namespace codablecash {

TableTransactionScanner::TableTransactionScanner(CdbTransaction* trx, TableStore* tableStore)
	: AbstractTransactionScanner(trx) {
	this->tableStore = tableStore;
	this->internalScanner = nullptr;
	this->nextRecord = nullptr;
	this->scanedStore = false;
}

TableTransactionScanner::~TableTransactionScanner() {
	shutdown();

	this->tableStore = nullptr;
}

void TableTransactionScanner::start() {
	this->internalScanner = new RecordScanner(this->tableStore);
	this->internalScanner->start();

}

bool TableTransactionScanner::hasNext() {
	if(!this->scanedStore && this->internalScanner->hasNext()){
		// check updated

		this->nextRecord = this->internalScanner->next();
		this->nextRecord = checkUpdated(this->nextRecord);

		return true;
	}
	else if(!this->scanedStore){
		this->scanedStore = true;
	}

	if(hasInsertedRecord()){
		this->nextRecord = nextInsertedRecord();
		return true;
	}

	return false;
}

const CdbRecord* TableTransactionScanner::next() {
	return this->nextRecord;
}

void TableTransactionScanner::shutdown() {
	if(this->internalScanner != nullptr){
		this->internalScanner->shutdown();
		delete this->internalScanner;
		this->internalScanner = nullptr;
	}
}

} /* namespace codablecash */
