/*
 * TableTransactionIndexRangeScanner.h
 *
 *  Created on: 2021/01/06
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXRANGESCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXRANGESCANNER_H_

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class CdbTransaction;
class TableStore;


class TableTransactionIndexRangeScanner : public AbstractTransactionScanner, public IJoinLeftSource {
public:
	TableTransactionIndexRangeScanner(ScanResultMetadata* metadata, CdbTransaction* trx, TableStore* tableStore, const AbstractScanCondition* filterCondition);
	virtual ~TableTransactionIndexRangeScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXRANGESCANNER_H_ */
