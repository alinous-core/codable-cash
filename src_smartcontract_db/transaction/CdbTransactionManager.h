/*
 * CdbTransactionManager.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTIONMANAGER_H_
#define TRANSACTION_CDBTRANSACTIONMANAGER_H_

namespace codablecash {

class CdbTransaction;
class CodableDatabase;

class CdbTransactionManager {
public:
	explicit CdbTransactionManager(CodableDatabase* db);
	virtual ~CdbTransactionManager();

	CdbTransaction* newTransaction();

private:
	CodableDatabase* db;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTIONMANAGER_H_ */
