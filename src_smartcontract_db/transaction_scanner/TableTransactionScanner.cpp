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
	return this->internalScanner->hasNext();
}

const CdbRecord* TableTransactionScanner::next() {

}

void TableTransactionScanner::shutdown() {
	if(this->internalScanner != nullptr){
		this->internalScanner->shutdown();
		delete this->internalScanner;
		this->internalScanner = nullptr;
	}
}

} /* namespace codablecash */
