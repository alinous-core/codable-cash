/*
 * CdbTransaction.cpp
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#include "transaction/CdbTransaction.h"
#include "transaction/CdbTransactionManager.h"
#include "transaction/SchemaObjectIdPublisher.h"

#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"
#include "engine/CdbOid.h"

#include "schema_table/table_record/CdbTableIdentifier.h"

#include "schema_table/schema/Schema.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableIndex.h"

#include "schema_table/table_store/CdbStorageManager.h"
#include "schema_table/table_store/TableStore.h"
#include "schema_table/table_store/IndexStore.h"

#include "transaction_scanner/TableTransactionScanner.h"

#include "transaction_update_cache/TransactionUpdateCache.h"

#include "schema_table/table/CdbTableColumn.h"

#include "schema_table/table_record_key/CdbRecordKey.h"

#include "scan_select/scan/IndexRecordScanner.h"

#include "transaction_log_alter/AbstractAlterCommandLog.h"

#include "transaction_log/DropTableLog.h"

namespace codablecash {

CdbTransaction::CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId) {
	this->trxManager = trxManager;
	this->transactionId = transactionId;

	CodableDatabase* db = trxManager->getDb();

	CdbLocalCacheManager* cacheManager = db->getLocalCacheManager();
	LocalOidFactory* localOidFactory = db->getLocalOidFactory();

	this->updateCache = new TransactionUpdateCache(cacheManager, localOidFactory);
}

CdbTransaction::~CdbTransaction() {
	this->trxManager = nullptr;
	this->cmdList.deleteElements();
	delete this->updateCache;
}

void CdbTransaction::commit() {
	while(!this->cmdList.isEmpty()){
		AbstractTransactionLog* cmd = nullptr;

		try{
			cmd = this->cmdList.remove(0);
			cmd->commit(this->trxManager);
		}
		catch(CdbException* e){
			e->setCmd(cmd);
			rollback();
			throw e;
		}
	}
}

void CdbTransaction::rollback() {
	this->cmdList.deleteElements();
	this->cmdList.reset();
}

void CdbTransaction::createTable(CreateTableLog* cmd) {
	this->cmdList.addElement(cmd);
}

void CdbTransaction::dropTable(DropTableLog* cmd) {
	this->cmdList.addElement(cmd);
}

void CdbTransaction::alterTable(AbstractAlterCommandLog* cmd) {
	this->cmdList.addElement(cmd);
}

void CdbTransaction::insert(InsertLog* cmd) {
	CdbTable* table = getTableFromIdentifier(cmd->getCdbTableIdentifier());

	this->updateCache->updateInsert(cmd, table);
	this->cmdList.addElement(cmd);
}

TableTransactionScanner* CdbTransaction::getTableTransactionScanner(const CdbTableIdentifier* tableId, AbstractScanCondition* condition) {
	CdbTable* table = getTableFromIdentifier(tableId);

	const CdbOid* oid = table->getOid();
	CdbStorageManager* store = this->trxManager->getStorageManager();

	TableStore* tableStore = store->getTableStore(oid);

	TableTransactionScanner* scanner = new TableTransactionScanner(this, tableStore);

	return scanner;
}

TransactionUpdateCache* CdbTransaction::getUpdateCache() const noexcept {
	return this->updateCache;
}

IndexScanner* CdbTransaction::getRawIndexScanner(const CdbTableIdentifier* tableId, const UnicodeString* columnName,
		CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	ArrayList<const UnicodeString> list;
	list.addElement(columnName);

	return getRawIndexScanner(tableId, &list, begin, beginEq, end, endEq);
}

IndexScanner* CdbTransaction::getRawIndexScanner(const CdbTableIdentifier* tableId, const ArrayList<const UnicodeString>* columnlist,
		CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	CdbTable* table = getTableFromIdentifier(tableId);

	ArrayList<const CdbOid> columnOidList;
	convertColumnName2OidList(table, columnlist, &columnOidList);

	return getRawIndexScanner(tableId, &columnOidList, begin, beginEq, end, endEq);
}

void CdbTransaction::convertColumnName2OidList(const CdbTable* table, const ArrayList<const UnicodeString>* columnlist,
		ArrayList<const CdbOid>* columnOidList) const {
	int maxLoop = columnlist->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* name = columnlist->get(i);

		CdbTableColumn* col = table->getColumn(name);
		if(col == nullptr){
			throw new CdbException(L"Column does not exists", __FILE__, __LINE__);
		}

		const CdbOid* colOid = col->getOid();
		columnOidList->addElement(colOid);
	}
}

IndexScanner* CdbTransaction::getRawIndexScanner(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList,
		CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	IndexStore* indexStore = getIndexStoreFromIdentifier(tableId, columnOidList);
	assert(indexStore != nullptr);

	IndexScanner* scanner = indexStore->getScanner(begin, beginEq, end, endEq);
	assert(scanner != nullptr);

	return scanner;
}

IndexRecordScanner* CdbTransaction::getIndexRecordScanner(const CdbTableIdentifier* tableId, const UnicodeString* columnName,
		CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	ArrayList<const UnicodeString> list;
	list.addElement(columnName);

	return getIndexRecordScanner(tableId, &list, begin, beginEq, end, endEq);
}


IndexRecordScanner* CdbTransaction::getIndexRecordScanner(const CdbTableIdentifier* tableId,
		const ArrayList<const UnicodeString>* columnlist, CdbRecordKey* begin,
		bool beginEq, CdbRecordKey* end, bool endEq) {
	CdbTable* table = getTableFromIdentifier(tableId);

	ArrayList<const CdbOid> columnOidList;
	convertColumnName2OidList(table, columnlist, &columnOidList);

	return getIndexRecordScanner(tableId, &columnOidList, begin, beginEq, end, endEq);
}


IndexRecordScanner* CdbTransaction::getIndexRecordScanner(const CdbTableIdentifier* tableId,
		const ArrayList<const CdbOid>* columnOidList, CdbRecordKey* begin,
		bool beginEq, CdbRecordKey* end, bool endEq) {

	IndexScanner* indexScanner = getRawIndexScanner(tableId, columnOidList, begin, beginEq, end, endEq);
	TableStore* tableStore = getTableStoreFromIdentifier(tableId);

	IndexRecordScanner* scanner = new IndexRecordScanner(indexScanner, tableStore);
	return scanner;
}

IndexStore* CdbTransaction::getIndexStoreFromIdentifier(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList) const {
	CdbTable* table = getTableFromIdentifier(tableId);

	CdbTableIndex* index = table->getIndexByColumnOids(columnOidList);
	if(index == nullptr){
		throw new CdbException(L"Index does not exists", __FILE__, __LINE__);
	}

	TableStore* tableStore = getTableStoreFromIdentifier(tableId);
	assert(tableStore != nullptr);

	IndexStore* indexStore = tableStore->getIndexStore(index->getOid());
	return indexStore;
}

TableStore* CdbTransaction::getTableStoreFromIdentifier(const CdbTableIdentifier* tableId) const {
	CdbTable* table = getTableFromIdentifier(tableId);

	CdbStorageManager* store = this->trxManager->getStorageManager();

	const CdbOid* tableoid = table->getOid();
	TableStore* tableStore = store->getTableStore(tableoid);
	assert(tableStore != nullptr);

	return tableStore;
}

CdbTable* CdbTransaction::getTableFromIdentifier(const CdbTableIdentifier* tableId) const {
	const UnicodeString* schemaName = tableId->getSchema();
	const UnicodeString* tableName = tableId->getTable();

	Schema* schema = this->trxManager->getSchema(schemaName);
	if(schema == nullptr){
		throw new CdbException(L"Schema does not exists", __FILE__, __LINE__);
	}

	CdbTable* table = schema->getCdbTableByName(tableName);
	if(table == nullptr){
		throw new CdbException(L"Table does not exists", __FILE__, __LINE__);
	}

	return table;
}

} /* namespace codablecash */
