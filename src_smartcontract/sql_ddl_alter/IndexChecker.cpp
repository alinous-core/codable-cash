/*
 * IndexChecker.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "sql_ddl_alter/IndexChecker.h"

#include "schema/SchemaManager.h"

#include "table_store/CdbStorageManager.h"

namespace codablecash {

IndexChecker::IndexChecker(SchemaManager* scmagr, CdbStorageManager* storagemgr)
		: scmagr(scmagr), storagemgr(storagemgr) {

}

IndexChecker::~IndexChecker() {

}

} /* namespace codablecash */
