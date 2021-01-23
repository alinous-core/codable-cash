/*
 * RightTableBufferedOidTransactionScanner.h
 *
 *  Created on: 2020/12/24
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDOIDTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDOIDTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"


namespace codablecash {

class RightTableBufferedOidTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableBufferedOidTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
			const CdbTable* table, const AbstractScanCondition* filterCondition);
	virtual ~RightTableBufferedOidTransactionScanner();

	virtual void start();
	virtual void reset(const AbstractCdbKey* key);

	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDOIDTRANSACTIONSCANNER_H_ */
