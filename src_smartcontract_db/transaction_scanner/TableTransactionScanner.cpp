/*
 * TableTransactionScan.cpp
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#include "transaction_scanner/TableTransactionScanner.h"

#include "transaction/CdbTransaction.h"

#include "scan_select/scan/RecordScanner.h"

#include "schema_table/table_store/TableStore.h"

#include "engine_lock/AbstractLockHandle.h"
#include "engine_lock/AbstractDatabaseLock.h"

namespace codablecash {

TableTransactionScanner::TableTransactionScanner(CdbTransaction* trx, TableStore* tableStore)
	: AbstractTransactionScanner(trx, tableStore->getTable()) {
	this->tableStore = tableStore;
	this->internalScanner = nullptr;
	this->nextRecord = nullptr;
	this->scanedStore = false;
	this->lockHandle = nullptr;
}

TableTransactionScanner::~TableTransactionScanner() {
	shutdown();

	this->tableStore = nullptr;
}

void TableTransactionScanner::shutdown() {
	if(this->internalScanner != nullptr){
		this->internalScanner->shutdown();
		delete this->internalScanner;
		this->internalScanner = nullptr;

		AbstractDatabaseLock* lock = this->lockHandle->getLock();
		lock->unclockHandle(this->lockHandle);
		this->lockHandle = nullptr;
	}
}

void TableTransactionScanner::start() {
	this->lockHandle = this->tableStore->readLock();

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


} /* namespace codablecash */
