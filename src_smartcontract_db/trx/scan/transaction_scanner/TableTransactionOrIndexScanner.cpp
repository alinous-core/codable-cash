/*
 * TableTransactionOrIndexScanner.cpp
 *
 *  Created on: 2020/12/11
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner/TableTransactionOrIndexScanner.h"

#include "schema_table/table_store/TableStore.h"

namespace codablecash {

TableTransactionOrIndexScanner::TableTransactionOrIndexScanner(CdbTransaction* trx, TableStore* tableStore)
		: AbstractTransactionScanner(trx, tableStore->getTable()){
	// TODO Auto-generated constructor stub

}

TableTransactionOrIndexScanner::~TableTransactionOrIndexScanner() {
	// TODO Auto-generated destructor stub
}

} /* namespace codablecash */
