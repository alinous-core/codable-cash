/*
 * TableTransactionScan.h
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_TABLETRANSACTIONSCAN_H_
#define TRANSACTION_SCANNER_TABLETRANSACTIONSCAN_H_

#include "transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class TableTransactionScan : public AbstractTransactionScanner {
public:
	TableTransactionScan();
	virtual ~TableTransactionScan();
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_TABLETRANSACTIONSCAN_H_ */
