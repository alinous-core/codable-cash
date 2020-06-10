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

class TableTransactionScanner : public AbstractTransactionScanner {
public:
	TableTransactionScanner();
	virtual ~TableTransactionScanner();
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_TABLETRANSACTIONSCANNER_H_ */
