/*
 * CdbTransaction.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTION_H_
#define TRANSACTION_CDBTRANSACTION_H_
#include <cstdint>

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTransactionManager;
class AbstractTransactionLog;
class CreateTableLog;
class InsertLog;
class TableTransactionScanner;
class AbstractScanCondition;
class CdbTableIdentifier;

class CdbTransaction {
public:
	CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId);
	virtual ~CdbTransaction();

	void commit();
	void rollback();

	void createTable(CreateTableLog* cmd);

	void insert(InsertLog* cmd) noexcept;

	TableTransactionScanner* getTableTransactionScanner(const CdbTableIdentifier* tableId, AbstractScanCondition* condition);
private:
	CdbTransactionManager* trxManager;
	uint64_t transactionId;

	ArrayList<AbstractTransactionLog> cmdList;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTION_H_ */
