/*
 * CdbTransactionManager.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTIONMANAGER_H_
#define TRANSACTION_CDBTRANSACTIONMANAGER_H_
#include <cstdint>

#include "schema/ISchemaUptateListner.h"

namespace codablecash {

class CdbTransaction;
class CodableDatabase;
class SchemaObjectIdPublisher;

class CdbTransactionManager : public ISchemaUptateListner {
public:
	explicit CdbTransactionManager(CodableDatabase* db);
	virtual ~CdbTransactionManager();

	virtual void schemaLoaded(Schema* sc);

	CdbTransaction* newTransaction(uint64_t transactionId);

	SchemaObjectIdPublisher* getSchemaObjectIdPublisher() const noexcept;
private:
	CodableDatabase* db;
	SchemaObjectIdPublisher* schemaIdPublisher;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTIONMANAGER_H_ */
