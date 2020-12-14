/*
 * TableTransactionOrIndexScanner.cpp
 *
 *  Created on: 2020/12/11
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner/TableTransactionOrIndexScanner.h"

#include "schema_table/table_store/TableStore.h"

namespace codablecash {

TableTransactionOrIndexScanner::TableTransactionOrIndexScanner(CdbTransaction* trx, TableStore* tableStore, const OrIndexWrapperCollection* index)
		: AbstractTransactionScanner(trx, tableStore->getTable()){
	// TODO Auto-generated constructor stub

}

TableTransactionOrIndexScanner::~TableTransactionOrIndexScanner() {
	// TODO Auto-generated destructor stub
}

void TableTransactionOrIndexScanner::start() {
}

bool TableTransactionOrIndexScanner::hasNext() {
}

const CdbRecord* TableTransactionOrIndexScanner::next() {
}

void TableTransactionOrIndexScanner::shutdown() {
}


} /* namespace codablecash */
