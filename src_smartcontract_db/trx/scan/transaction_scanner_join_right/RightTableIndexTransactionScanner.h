/*
 * RightTableIndexTransactionScanner.h
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class RightTableIndexTransactionScanner : public IJoinLeftSource, public AbstractTransactionScanner {
public:
	RightTableIndexTransactionScanner();
	virtual ~RightTableIndexTransactionScanner();
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_ */
