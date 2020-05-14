/*
 * CdbTransactionManager.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTIONMANAGER_H_
#define TRANSACTION_CDBTRANSACTIONMANAGER_H_
#include <cstdint>

namespace codablecash {

class CdbTransaction;
class CodableDatabase;
class SchemaObjectIdPublisher;

class CdbTransactionManager {
public:
	explicit CdbTransactionManager(CodableDatabase* db);
	virtual ~CdbTransactionManager();

	CdbTransaction* newTransaction(uint64_t transactionId);

private:
	CodableDatabase* db;
	SchemaObjectIdPublisher* schemaIdPublisher;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTIONMANAGER_H_ */
