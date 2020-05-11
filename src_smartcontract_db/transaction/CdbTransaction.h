/*
 * CdbTransaction.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTION_H_
#define TRANSACTION_CDBTRANSACTION_H_

namespace codablecash {

class CdbTransactionManager;

class CdbTransaction {
public:
	explicit CdbTransaction(CdbTransactionManager* trxManager);
	virtual ~CdbTransaction();

private:
	CdbTransactionManager* trxManager;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTION_H_ */
