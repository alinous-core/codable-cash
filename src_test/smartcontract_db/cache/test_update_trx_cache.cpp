/*
 * test_update_trx_cache.cpp
 *
 *  Created on: 2020/09/30
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbOid.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"

#include "transaction/CdbTransaction.h"

#include "transaction_update_cache/TransactionUpdateCache.h"

#include "../toolkit/TestDbSchema01.h"

#include "table_record/CdbRecord.h"
#include "table_record_value/CdbIntValue.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestUpdateTrxCacheGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

static CdbRecord* makeRecord(uint64_t loid, int value);
CdbRecord* makeRecord(uint64_t loid, int value){
	CdbRecord* record = new CdbRecord();
	CdbOid oid(loid);
	record->setOid(&oid);

	CdbIntValue* cvalue = new CdbIntValue(value);
	record->addValue(cvalue);

	return record;
}

TEST(TestUpdateTrxCacheGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		CodableDatabase* db = tester.getDatabase();

		SchemaManager* schema = db->getSchemaManager();
		CdbTable* table = schema->getTable(L"public", L"test_table");

		CdbTransaction* trx = db->newTransaction(); __STP(trx);
		TransactionUpdateCache* cache = trx->getUpdateCache();

	}
}

