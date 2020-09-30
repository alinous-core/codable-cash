/*
 * CdbTransactionManager.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "transaction/CdbTransactionManager.h"
#include "transaction/CdbTransaction.h"
#include "transaction/SchemaObjectIdPublisher.h"
#include "transaction/RecordObjectIdPublisher.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"
#include "schema/Schema.h"

#include "table_record/CdbTableIdentifier.h"

#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"

#include "transaction_log_alter/AbstractAlterCommandLog.h"
#include "transaction_log_alter/AlterAddColumnCommandLog.h"
#include "transaction_log_alter/AlterAddIndexCommandLog.h"
#include "transaction_log_alter/AlterDropIndexCommandLog.h"
#include "transaction_log_alter/AlterDropColumnCommandLog.h"
#include "transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "transaction_log_alter_modify/AlterModifyCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"
#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

#include "engine_lock/StackDbLockUnlocker.h"
namespace codablecash {

CdbTransactionManager::CdbTransactionManager(CodableDatabase* db) {
	this->db = db;
	this->schemaIdPublisher = nullptr;
	this->recordObjectIdPublisher = nullptr;
	this->schemaManager = nullptr;
	this->committedCommands = new ArrayList<AbstractTransactionLog>();
}

CdbTransactionManager::~CdbTransactionManager() {
	this->db = nullptr;
	delete this->schemaIdPublisher;
	this->schemaManager = nullptr;

	delete this->recordObjectIdPublisher;
	this->recordObjectIdPublisher = nullptr;

	this->committedCommands->deleteElements();
	delete this->committedCommands;
}

void CdbTransactionManager::schemaLoaded(SchemaManager* sc) {
	delete this->schemaIdPublisher;
	this->schemaIdPublisher = new SchemaObjectIdPublisher(sc);
	this->recordObjectIdPublisher = new RecordObjectIdPublisher(sc);

	this->schemaManager = sc;
}

void CdbTransactionManager::onCreateTable(SchemaManager* mgr, const CdbTable* table) {
	// do nothing
}

void CdbTransactionManager::onAlterModify(SchemaManager* mgr,
		const CdbTable* table, const ColumnModifyContext* ctx) {
	// do nothing
}

CdbTransaction* CdbTransactionManager::newTransaction(uint64_t transactionId) {
	CdbTransaction* trx = new CdbTransaction(this, transactionId);

	return trx;
}

SchemaObjectIdPublisher* CdbTransactionManager::getSchemaObjectIdPublisher() const noexcept {
	return this->schemaIdPublisher;
}

RecordObjectIdPublisher* CdbTransactionManager::getRecordObjectIdPublisher() const noexcept {
	return this->recordObjectIdPublisher;
}

void CdbTransactionManager::commitCreateTable(CreateTableLog* cmd) {
	CdbTable* table = cmd->getTable();
	this->schemaManager->createTable(table);

	this->committedCommands->addElement(cmd);
}

void CdbTransactionManager::commitAlterTable(AbstractAlterCommandLog* cmd) {
	uint8_t type = cmd->getType();

	switch(type){
	case AbstractAlterCommandLog::TRX_ALTER_ADD_INDEX:
		handleAlterTableAddIndex(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_ADD_COLUMN:
		handleAlterTableAddColumn(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_DROP_INDEX:
		handleAlterTableDropIndex(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_DROP_COLUMN:
		handleAlterTableDropColumn(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_ADD_PRIMARY_KEY:
		handleAlterTableAddPrimaryKey(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_DROP_PRIMARY_KEY:
		handleAlterTableDropPrimaryKey(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_MODIFY:
		handleAlterTableModify(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_RENAME_COLUMN:
		handleAlterTableRenameColumn(cmd);
		break;
	case AbstractAlterCommandLog::TRX_ALTER_RENAME_TABLE:
		handleAlterTableRenameTable(cmd);
		break;
	default:
		throw new CdbException(L"unknown command type.", __FILE__, __LINE__);
	}

	this->committedCommands->addElement(cmd);
}

void CdbTransactionManager::handleAlterTableAddIndex(AbstractAlterCommandLog* cmd) {
	AlterAddIndexCommandLog* cmdlog = dynamic_cast<AlterAddIndexCommandLog*>(cmd);
	this->schemaManager->handleAlterTableAddIndex(cmdlog);
}

void CdbTransactionManager::handleAlterTableAddColumn(AbstractAlterCommandLog* cmd) {
	AlterAddColumnCommandLog* cmdlog = dynamic_cast<AlterAddColumnCommandLog*>(cmd);
	this->schemaManager->handleAlterTableAddColumn(cmdlog);
}

void CdbTransactionManager::handleAlterTableDropIndex(AbstractAlterCommandLog* cmd) {
	AlterDropIndexCommandLog* cmdlog = dynamic_cast<AlterDropIndexCommandLog*>(cmd);
	this->schemaManager->handleAlterTableDropIndex(cmdlog);
}

void CdbTransactionManager::handleAlterTableDropColumn(AbstractAlterCommandLog* cmd) {
	AlterDropColumnCommandLog* cmdlog = dynamic_cast<AlterDropColumnCommandLog*>(cmd);
	this->schemaManager->handleAlterTableDropColumn(cmdlog);
}

void CdbTransactionManager::handleAlterTableAddPrimaryKey(AbstractAlterCommandLog* cmd) {
	AlterAddPrimaryKeyCommandLog* cmdlog = dynamic_cast<AlterAddPrimaryKeyCommandLog*>(cmd);
	this->schemaManager->handleAlterTableAddPrimaryKey(cmdlog);
}

void CdbTransactionManager::handleAlterTableDropPrimaryKey(AbstractAlterCommandLog* cmd) {
	AlterDropPrimaryKeyCommandLog* cmdlog = dynamic_cast<AlterDropPrimaryKeyCommandLog*>(cmd);
	this->schemaManager->handleAlterTableDropPrimaryKey(cmdlog);
}

void CdbTransactionManager::handleAlterTableModify(AbstractAlterCommandLog* cmd) {
	AlterModifyCommandLog* cmdlog = dynamic_cast<AlterModifyCommandLog*>(cmd);
	this->schemaManager->handleAlterTableModify(cmdlog);
}

void CdbTransactionManager::handleAlterTableRenameColumn(AbstractAlterCommandLog* cmd) {
	AlterRenameColumnCommandLog* cmdlog = dynamic_cast<AlterRenameColumnCommandLog*>(cmd);
	this->schemaManager->handleAlterTableRenameColumn(cmdlog);
}

void CdbTransactionManager::handleAlterTableRenameTable(AbstractAlterCommandLog* cmd) {
	AlterRenameTableCommandLog* cmdlog = dynamic_cast<AlterRenameTableCommandLog*>(cmd);
	this->schemaManager->handleAlterTableRenameTable(cmdlog);
}

void CdbTransactionManager::commitInsert(InsertLog* cmd) {
	CdbTableIdentifier* tableIdentifier = cmd->getCdbTableIdentifier();
	const UnicodeString* schemaName = tableIdentifier->getSchema();
	const UnicodeString* tableName = tableIdentifier->getTable();

	Schema* schema = this->schemaManager->getSchema(schemaName);
	if(schema == nullptr){
		throw new CdbException(L"Schema to INSERT TABLE does not exists.", __FILE__, __LINE__);
	}

	CdbTable* table = schema->getCdbTableByName(tableName);
	const CdbOid* oid = table->getOid();

	CdbStorageManager* storeManager = this->db->getStorageManager();
	TableStore* store = storeManager->getTableStore(oid);
	assert(store != nullptr);

	// table level lock
	{
		AbstractLockHandle* lockH = store->writeLock();
		StackDbLockUnlocker unlocker(lockH);

		const ArrayList<CdbRecord>* records = cmd->getRecords();

		int maxLoop = records->size();
		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* rec = records->get(i);
			store->validateRecord(rec);
		}


		for(int i = 0; i != maxLoop; ++i){
			CdbRecord* rec = records->get(i);

			store->insert(rec);
		}

		this->committedCommands->addElement(cmd);
	}
}

Schema* CdbTransactionManager::getSchema(const UnicodeString* name) const noexcept {
	return this->schemaManager->getSchema(name);
}

CdbStorageManager* CdbTransactionManager::getStorageManager() const noexcept {
	return this->db->getStorageManager();
}

ReadLockHandle* CdbTransactionManager::databaseReadLock() {
	return this->db->databaseReadLock();
}

WriteLockHandle* CdbTransactionManager::databaseWriteLock() {
	return this->db->databaseWriteLock();
}

} /* namespace codablecash */
