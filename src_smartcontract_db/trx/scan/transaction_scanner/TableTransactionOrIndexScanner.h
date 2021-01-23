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
class OrIndexWrapperCollection;

class TableTransactionOrIndexScanner : public AbstractTransactionScanner, public IJoinLeftSource {
public:
	TableTransactionOrIndexScanner(ScanResultMetadata* metadata, CdbTransaction* trx, TableStore* tableStore
			, const AbstractScanCondition* filterCondition, const OrIndexWrapperCollection* index);
	virtual ~TableTransactionOrIndexScanner();

	virtual void start();
	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();

private:
	const OrIndexWrapperCollection* index;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_TABLETRANSACTIONORINDEXSCANNER_H_ */
