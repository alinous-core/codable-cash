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

#include "table_record_key/CdbRecordKey.h"
#include "table_record/CdbRecord.h"

namespace codablecash {

IndexChecker::IndexChecker(CodableDatabase* db)
		: db(db) {

}

IndexChecker::~IndexChecker() {

}

bool IndexChecker::checkUnique(const CdbTable* table, const CdbTableColumn* column) {
	ArrayList<const CdbTableColumn> list;
	list.addElement(column);

	return checkUnique(table, &list);
}

bool IndexChecker::checkUnique(const CdbTable* table, ArrayList<const CdbTableColumn>* column) {
	CdbLocalCacheManager* cacheMgr = this->db->getLocalCacheManager();
	SingleKeyOidCache* cache = cacheMgr->createSingleKeyOidCache(); __STP(cache);

	CdbStorageManager* storeMgr = this->db->getStorageManager();
	TableStore* store = storeMgr->getTableStore(table->getOid());

	bool ret = true;

	RecordScanner scanner(store);

	scanner.start();
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

		CdbRecordKey* key = makeIndexKey(record, column);

		if(cache->hasKey(key)){
			ret = false;
			break;
		}

		cache->insert(key, record->getOid());
	}

	return ret;
}

CdbRecordKey* IndexChecker::makeIndexKey(const CdbRecord* record, ArrayList<const CdbTableColumn>* column) {
}

} /* namespace codablecash */
