/*
 * RightTableTransactionScanner.h
 *
 *  Created on: 2020/12/19
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class AbstractJoinCandidate;

class RightTableBufferedTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableBufferedTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table, AbstractJoinCandidate* joinCandidate);
	virtual ~RightTableBufferedTransactionScanner();

	virtual void start();
	virtual void reset(const AbstractCdbKey* key);

	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();

private:
	AbstractJoinCandidate* joinCandidate;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEBUFFEREDTRANSACTIONSCANNER_H_ */
