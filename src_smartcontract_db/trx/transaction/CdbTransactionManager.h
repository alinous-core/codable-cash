/*
 * CdbTransactionManager.h
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTIONMANAGER_H_
#define TRANSACTION_CDBTRANSACTIONMANAGER_H_
#include <cstdint>

#include "schema_table/schema/ISchemaUptateListner.h"

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTransaction;
class CodableDatabase;
class SchemaObjectIdPublisher;
class RecordObjectIdPublisher;
class CreateTableLog;
class DropTableLog;
class AbstractTransactionLog;
class InsertLog;
class Schema;
class CdbStorageManager;
class ReadLockHandle;
class WriteLockHandle;
class AbstractAlterCommandLog;

class CdbTransactionManager : public ISchemaUptateListner {
public:
	explicit CdbTransactionManager(CodableDatabase* db);
	virtual ~CdbTransactionManager();

	virtual void schemaLoaded(SchemaManager* sc);
	virtual void onCreateTable(SchemaManager* mgr, const CdbTable* table);
	virtual void onDropTable(SchemaManager* mgr, const CdbTable* table);

	virtual void onAlterModify(SchemaManager* mgr, const CdbTable* table, const ColumnModifyContext* ctx);
	virtual void onDropPrimaryKey(SchemaManager* mgr, const CdbTable* table, const CdbTableIndex* primaryKey);
	virtual void onAddPrimaryKey(SchemaManager* mgr, const CdbTable* table, const CdbTableIndex* primaryKey);
	virtual void onAlterTableRenameTable(SchemaManager* mgr, const CdbTable* table, TableRenameContext* ctx);
	virtual void onAddColumn(SchemaManager* mgr, const CdbTable* table, const CdbTableColumn* newColumn, const CdbTableIndex* newUniqueIndex);
	virtual void onDropColumn(SchemaManager* mgr, const CdbTable* table, const CdbTableColumn* removalColumn, const ArrayList<CdbTableIndex>* removalIndexes);
	virtual void onAddIndex(SchemaManager* mgr, const CdbTable* table, const CdbTableIndex* newIndex);
	virtual void onDropIndex(SchemaManager* mgr, const CdbTable* table, const CdbTableIndex* removalIndex);

	CdbTransaction* newTransaction(uint64_t transactionId);

	SchemaObjectIdPublisher* getSchemaObjectIdPublisher() const noexcept;
	RecordObjectIdPublisher* getRecordObjectIdPublisher() const noexcept;

	void commitCreateTable(CreateTableLog* cmd);
	void commitDropTable(DropTableLog* cmd);
	void commitAlterTable(AbstractAlterCommandLog* cmd);

	void commitInsert(InsertLog* cmd);

	Schema* getSchema(const UnicodeString* name) const noexcept;

	CdbStorageManager* getStorageManager() const noexcept;

	ReadLockHandle* databaseReadLock();
	WriteLockHandle* databaseWriteLock();

	CodableDatabase* getDb() const noexcept {
		return db;
	}

private:
	void handleAlterTableAddIndex(AbstractAlterCommandLog* cmd);
	void handleAlterTableAddColumn(AbstractAlterCommandLog* cmd);
	void handleAlterTableDropIndex(AbstractAlterCommandLog* cmd);
	void handleAlterTableDropColumn(AbstractAlterCommandLog* cmd);
	void handleAlterTableAddPrimaryKey(AbstractAlterCommandLog* cmd);
	void handleAlterTableDropPrimaryKey(AbstractAlterCommandLog* cmd);
	void handleAlterTableModify(AbstractAlterCommandLog* cmd);
	void handleAlterTableRenameColumn(AbstractAlterCommandLog* cmd);
	void handleAlterTableRenameTable(AbstractAlterCommandLog* cmd);

private:
	CodableDatabase* db;
	SchemaManager* schemaManager;
	SchemaObjectIdPublisher* schemaIdPublisher;
	RecordObjectIdPublisher* recordObjectIdPublisher;

	ArrayList<AbstractTransactionLog>* committedCommands;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTIONMANAGER_H_ */
