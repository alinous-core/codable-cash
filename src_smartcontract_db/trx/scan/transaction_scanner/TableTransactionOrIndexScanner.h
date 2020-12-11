/*
 * TableTransactionOrIndexScanner.h
 *
 *  Created on: 2020/12/11
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONORINDEXSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONORINDEXSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class CdbTransaction;
class TableStore;

class TableTransactionOrIndexScanner : public AbstractTransactionScanner, public IJoinLeftSource {
public:
	TableTransactionOrIndexScanner(CdbTransaction* trx, TableStore* tableStore);
	virtual ~TableTransactionOrIndexScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONORINDEXSCANNER_H_ */
