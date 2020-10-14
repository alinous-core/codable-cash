/*
 * IndexChecker.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl_alter/IndexChecker.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbLocalCacheManager.h"

#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTable.h"

#include "schema_table/table_store/CdbStorageManager.h"

#include "scan_select/scan/RecordScanner.h"

#include "base/StackRelease.h"

#include "trx/transaction_cache/SingleKeyOidCache.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_key/CdbRecordKey.h"
#include "schema_table/record/table_record_key/AbstractCdbKey.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"
#include "schema_table/record/table_record_value/CdbValueCaster.h"

#include "schema_table/table_store/RecordValueConverter.h"

#include "schema_table/schema_alter_ctx/ColumnModifyContext.h"

#include "btreekey/NullKey.h"

#include "btree/AbstractBtreeKey.h"

using namespace alinous;

namespace codablecash {

IndexChecker::IndexChecker(CodableDatabase* db, const ColumnModifyContext* modifyContext)
		: db(db) {
	CdbTableColumn* column = modifyContext->getColumn();

	this->pos = column->getPosition();
	this->isnotnull = modifyContext->isNotNull();
	this->cdbType = modifyContext->getCdbType();
	this->length = modifyContext->getLength();
	this->defaultValue = modifyContext->getDefaultValue();
}

IndexChecker::IndexChecker(CodableDatabase* db) : db(db) {
	this->pos = -1;
	this->isnotnull = false;
	this->cdbType = false;
	this->length = -1;

	this->defaultValue = nullptr;
}

IndexChecker::~IndexChecker() {
	this->defaultValue = nullptr;
}

bool IndexChecker::checkUnique(const CdbTable* table, const ArrayList<const CdbOid>* columnOidlist, bool update) {
	ArrayList<const CdbTableColumn> columnList;

	int maxLoop = columnOidlist->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbOid* columnOid = columnOidlist->get(i);

		const CdbTableColumn* column = table->getColumn(columnOid);
		columnList.addElement(column);
	}

	return checkUnique(table, &columnList, update);
}


bool IndexChecker::checkUnique(const CdbTable* table, const CdbTableColumn* column, bool update) {
	ArrayList<const CdbTableColumn> list;
	list.addElement(column);

	return checkUnique(table, &list, update);
}

bool IndexChecker::checkUnique(const CdbTable* table, ArrayList<const CdbTableColumn>* columnList, bool update) {
	CdbLocalCacheManager* cacheMgr = this->db->getLocalCacheManager();
	SingleKeyOidCache* cache = cacheMgr->createSingleKeyOidCache(); __STP(cache);

	CdbStorageManager* storeMgr = this->db->getStorageManager();
	TableStore* store = storeMgr->getTableStore(table->getOid());

	bool ret = true;

	RecordScanner scanner(store);

	scanner.start();
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

		// RecordValueConverter
		CdbRecord* newRecord = nullptr;
		if(update){
			newRecord = getConvertedRecord(record);
			record = newRecord;
		}
		 __STP(newRecord);

		CdbRecordKey* key = makeIndexKey(record, columnList); __STP(key);
		if(cache->hasKey(key)){
			ret = false;
			break;
		}

		cache->insert(key, record->getOid());
	}

	return ret;
}

CdbRecord* IndexChecker::getConvertedRecord(const CdbRecord* record) {
	RecordValueConverter converter(this->pos, this->isnotnull, this->cdbType, this->length, this->defaultValue);

	CdbRecord* newRecord = converter.processUpdate(record);

	return newRecord;
}

CdbRecordKey* IndexChecker::makeIndexKey(const CdbRecord* record, ArrayList<const CdbTableColumn>* columnList) {
	CdbRecordKey* key = new CdbRecordKey();

	int maxLoop = columnList->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbTableColumn* column = columnList->get(i);
		int pos = column->getPosition();

		const AbstractCdbValue* v = record->get(pos);
		AbstractBtreeKey* vkey = v != nullptr? v->toKey() : nullptr;
		if(vkey == nullptr){
			vkey = new NullKey();
		}

		key->addKey(vkey);
	}

	return key;
}

} /* namespace codablecash */
