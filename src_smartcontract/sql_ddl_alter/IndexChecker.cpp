/*
 * IndexChecker.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "sql_ddl_alter/IndexChecker.h"

#include "engine/CodableDatabase.h"

#include "table/CdbTableColumn.h"

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

}


} /* namespace codablecash */
