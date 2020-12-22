/*
 * TableTransactionIndexScanner.cpp
 *
 *  Created on: 2020/12/10
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner/TableTransactionIndexScanner.h"

#include "schema_table/table_store/TableStore.h"

namespace codablecash {

TableTransactionIndexScanner::TableTransactionIndexScanner(ScanResultMetadata* metadata, CdbTransaction* trx, TableStore* tableStore)
			: AbstractTransactionScanner(metadata, trx, tableStore->getTable()){
	// TODO Auto-generated constructor stub

}

TableTransactionIndexScanner::~TableTransactionIndexScanner() {
	// TODO Auto-generated destructor stub
}

} /* namespace codablecash */
