/*
 * RightTableTransactionScanner.h
 *
 *  Created on: 2020/12/19
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLETRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLETRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class RightTableTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table);
	virtual ~RightTableTransactionScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLETRANSACTIONSCANNER_H_ */
