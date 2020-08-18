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

#include "engine/CdbException.h"
#include "engine/CdbOid.h"

#include "table_record/CdbTableIdentifier.h"

#include "schema/Schema.h"

#include "table/CdbTable.h"
#include "table/CdbTableIndex.h"

#include "table_store/CdbStorageManager.h"
#include "table_store/TableStore.h"
#include "table_store/IndexStore.h"

#include "transaction_scanner/TableTransactionScanner.h"

#include "transaction_update_cache/TransactionUpdateCache.h"

#include "table/CdbTableColumn.h"

#include "table_record_key/CdbRecordKey.h"

namespace codablecash {

CdbTransaction::CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId) {
	this->trxManager = trxManager;
	this->transactionId = transactionId;
	this->updateCache = new TransactionUpdateCache();
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
	commit();

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

	int maxLoop = columnlist->size();
	for(int i = 0; i != maxLoop; ++i){
		const UnicodeString* name = columnlist->get(i);

		CdbTableColumn* col = table->getColumn(name);
		if(col == nullptr){
			throw new CdbException(L"Column does not exists", __FILE__, __LINE__);
		}

		const CdbOid* colOid = col->getOid();
		columnOidList.addElement(colOid);
	}

	return getRawIndexScanner(tableId, &columnOidList, begin, beginEq, end, endEq);
}

IndexScanner* CdbTransaction::getRawIndexScanner(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList,
		CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq) {
	CdbTable* table = getTableFromIdentifier(tableId);

	CdbTableIndex* index = table->getIndexByColumnOids(columnOidList);
	if(index == nullptr){
		throw new CdbException(L"Index does not exists", __FILE__, __LINE__);
	}

	CdbStorageManager* store = this->trxManager->getStorageManager();

	const CdbOid* tableoid = table->getOid();
	TableStore* tableStore = store->getTableStore(tableoid);
	assert(tableStore != nullptr);

	IndexStore* indexStore = tableStore->getIndexStore(index->getOid());
	assert(indexStore != nullptr);

	IndexScanner* scanner = indexStore->getScanner(begin, beginEq, end, endEq);
	assert(scanner != nullptr);

	return scanner;
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
