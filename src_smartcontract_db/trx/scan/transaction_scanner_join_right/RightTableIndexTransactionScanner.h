/*
 * RightTableIndexTransactionScanner.h
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class RightTableIndexTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableIndexTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table);
	virtual ~RightTableIndexTransactionScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_ */
