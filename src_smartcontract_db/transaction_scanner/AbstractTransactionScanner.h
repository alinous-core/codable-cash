/*
 * AbstractTransactionScanner.h
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_
#define TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_

namespace codablecash {

class CdbTransaction;

class AbstractTransactionScanner {
public:
	explicit AbstractTransactionScanner(CdbTransaction* trx);
	virtual ~AbstractTransactionScanner();

	virtual void start() = 0;
	virtual void shutdown() = 0;

protected:
	CdbTransaction* trx;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_ */
