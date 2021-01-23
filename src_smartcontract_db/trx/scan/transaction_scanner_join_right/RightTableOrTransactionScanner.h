/*
 * RightTableOrTransactionScanner.h
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEORTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEORTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class JoinOrCandidate;

class RightTableOrTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableOrTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
			const CdbTable* table, const AbstractScanCondition* filterCondition, const JoinOrCandidate* orCandidate);
	virtual ~RightTableOrTransactionScanner();

	virtual void start();
	virtual void reset(const AbstractCdbKey* key);

	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();

private:
	JoinOrCandidate* orCandidate;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEORTRANSACTIONSCANNER_H_ */
