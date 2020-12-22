/*
 * TableTransactionIndexScanner.h
 *
 *  Created on: 2020/12/10
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXSCANNER_H_

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class CdbTransaction;
class TableStore;

class TableTransactionIndexScanner : public AbstractTransactionScanner, public IJoinLeftSource {
public:
	TableTransactionIndexScanner(ScanResultMetadata* metadata, CdbTransaction* trx, TableStore* tableStore);
	virtual ~TableTransactionIndexScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONINDEXSCANNER_H_ */
