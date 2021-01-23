/*
 * TableTransactionIndexRangeScanner.cpp
 *
 *  Created on: 2021/01/06
 *      Author: iizuka
 */

#include "trx/scan/transaction_scanner/TableTransactionIndexRangeScanner.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

#include "trx/transaction/CdbTransaction.h"

#include "schema_table/table_store/TableStore.h"

#include "trx/scan/transaction_scan_result/ScanResultMetadata.h"

namespace codablecash {

TableTransactionIndexRangeScanner::TableTransactionIndexRangeScanner(ScanResultMetadata* metadata,
		CdbTransaction* trx, TableStore* tableStore, const AbstractScanCondition* filterCondition)
		: AbstractTransactionScanner(metadata, trx, tableStore->getTable(), filterCondition){
	// TODO Auto-generated constructor stub

}

TableTransactionIndexRangeScanner::~TableTransactionIndexRangeScanner() {
	// TODO Auto-generated destructor stub
}

} /* namespace codablecash */
