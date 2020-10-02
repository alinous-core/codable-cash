/*
 * IndexChecker.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "sql_ddl_alter/IndexChecker.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbLocalCacheManager.h"

#include "table/CdbTableColumn.h"
#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"

#include "scan/RecordScanner.h"

#include "base/StackRelease.h"

#include "transaction_cache/SingleKeyOidCache.h"

#include "table_record/CdbRecord.h"

#include "table_record_key/CdbRecordKey.h"

#include "table_record_value/AbstractCdbValue.h"

#include "table_store/RecordValueConverter.h"

namespace codablecash {

IndexChecker::IndexChecker(CodableDatabase* db, const ColumnModifyContext* modifyContext)
		: db(db) {
	this->modifyContext = modifyContext;
}

IndexChecker::~IndexChecker() {

}

bool IndexChecker::checkUnique(const CdbTable* table, const CdbTableColumn* column) {
	ArrayList<const CdbTableColumn> list;
	list.addElement(column);

	return checkUnique(table, &list);
}

bool IndexChecker::checkUnique(const CdbTable* table, ArrayList<const CdbTableColumn>* columnList) {
	CdbLocalCacheManager* cacheMgr = this->db->getLocalCacheManager();
	SingleKeyOidCache* cache = cacheMgr->createSingleKeyOidCache(); __STP(cache);

	CdbStorageManager* storeMgr = this->db->getStorageManager();
	TableStore* store = storeMgr->getTableStore(table->getOid());

	bool ret = true;

	RecordScanner scanner(store);

	RecordValueConverter* conv = nullptr; // TODO:

	scanner.start();
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

		// RecordValueConverter

		CdbRecordKey* key = makeIndexKey(record, columnList); __STP(key);

		if(cache->hasKey(key)){
			ret = false;
			break;
		}

		cache->insert(key, record->getOid());
	}

	return ret;
}

CdbRecordKey* IndexChecker::makeIndexKey(const CdbRecord* record, ArrayList<const CdbTableColumn>* columnList) {
	CdbRecordKey* key = new CdbRecordKey();

	int maxLoop = columnList->size();
	for(int i = 0; i != maxLoop; ++i){
		const CdbTableColumn* column = columnList->get(i);
		int pos = column->getPosition();

		const AbstractCdbValue* v = record->get(pos);
		AbstractCdbKey* vkey = v != nullptr? v->toKey() : nullptr;
		key->addKey(vkey);
	}

	return key;
}

} /* namespace codablecash */
