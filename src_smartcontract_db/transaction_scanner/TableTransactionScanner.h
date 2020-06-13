/*
 * TableTransactionScan.h
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_
#define TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_

#include "transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class TableStore;
class RecordScanner;

class TableTransactionScanner : public AbstractTransactionScanner {
public:
	TableTransactionScanner(CdbTransaction* trx, TableStore* tableStore);
	virtual ~TableTransactionScanner();

	virtual void start();
	virtual bool hasNext();
	virtual CdbRecord* next();

	virtual void shutdown();
private:
	TableStore* tableStore;
	RecordScanner* internalScanner;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_ */
