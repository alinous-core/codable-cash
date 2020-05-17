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

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTransaction;
class CodableDatabase;
class SchemaObjectIdPublisher;
class CreateTableLog;
class AbstractTransactionLog;

class CdbTransactionManager : public ISchemaUptateListner {
public:
	explicit CdbTransactionManager(CodableDatabase* db);
	virtual ~CdbTransactionManager();

	virtual void schemaLoaded(SchemaManager* sc);
	virtual void onCreateTable(SchemaManager* mgr, CdbTable* table);

	CdbTransaction* newTransaction(uint64_t transactionId);

	SchemaObjectIdPublisher* getSchemaObjectIdPublisher() const noexcept;

	void commitCreateTable(CreateTableLog* cmd);
private:
	CodableDatabase* db;
	SchemaManager* schema;
	SchemaObjectIdPublisher* schemaIdPublisher;

	ArrayList<AbstractTransactionLog>* committedCommands;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTIONMANAGER_H_ */
