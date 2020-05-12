/*
 * CdbTransaction.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTION_H_
#define TRANSACTION_CDBTRANSACTION_H_
#include <cstdint>

namespace codablecash {

class CdbTransactionManager;
class AbstractTransactionLog;
class CreateTableLog;

class CdbTransaction {
public:
	CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId);
	virtual ~CdbTransaction();

	void commit();
	void rollback();

	void createTable(CreateTableLog* cmd);
private:
	CdbTransactionManager* trxManager;
	uint64_t transactionId;


};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTION_H_ */
