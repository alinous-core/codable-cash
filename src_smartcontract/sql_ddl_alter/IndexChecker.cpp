/*
 * IndexChecker.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "sql_ddl_alter/IndexChecker.h"

#include "engine/CodableDatabase.h"

#include "table/CdbTableColumn.h"
#include "table/CdbTable.h"

#include "table_store/CdbStorageManager.h"

#include "scan/RecordScanner.h"

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
	CdbStorageManager* storeMgr = this->db->getStorageManager();

	TableStore* store = storeMgr->getTableStore(table->getOid());

	bool ret = true;

	RecordScanner scanner(store);

	scanner.start();
	while(scanner.hasNext()){
		const CdbRecord* record = scanner.next();

	}

	return true;
}


} /* namespace codablecash */
