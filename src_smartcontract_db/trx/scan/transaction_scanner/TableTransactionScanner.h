/*
 * TableTransactionScan.h
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_
#define TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class TableStore;
class RecordScanner;
class AbstractLockHandle;

class TableTransactionScanner : public AbstractTransactionScanner, public IJoinLeftSource {
public:
	TableTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, TableStore* tableStore, const AbstractScanCondition* filterCondition);
	virtual ~TableTransactionScanner();

	virtual void start();
	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();
private:
	TableStore* tableStore;
	RecordScanner* internalScanner;

	const CdbRecord* nextRecord;
	bool scanedStore;

	AbstractLockHandle* lockHandle;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_ */
