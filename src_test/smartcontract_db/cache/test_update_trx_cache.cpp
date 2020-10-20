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

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"

#include "trx/transaction/CdbTransaction.h"

#include "trx/scan/transaction_update_cache/TransactionUpdateCache.h"
#include "trx/scan/transaction_update_cache/UpdatedRecordCursor.h"

#include "smartcontract_db/toolkit/TestDbSchema01.h"

#include "schema_table/record/table_record/CdbRecord.h"
#include "schema_table/record/table_record_value/CdbIntValue.h"

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

		CdbRecord* rec = makeRecord(1, 10); __STP(rec);

		cache->addUpdatedRecord(table, rec);

		bool result = cache->isUpdated(table, rec->getOid());
		CHECK(result);

		const CdbRecord* crec = cache->getUpdatedRecord(table, rec->getOid());
		CHECK(crec != nullptr);

		CHECK(crec->getOid()->equals(rec->getOid()));
	}
}

TEST(TestUpdateTrxCacheGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		CodableDatabase* db = tester.getDatabase();

		SchemaManager* schema = db->getSchemaManager();
		CdbTable* table = schema->getTable(L"public", L"test_table");

		CdbTransaction* trx = db->newTransaction(); __STP(trx);
		TransactionUpdateCache* cache = trx->getUpdateCache();

		ArrayList<CdbRecord> list;
		list.setDeleteOnExit();

		for(int i = 1; i != 11; ++i){
			CdbRecord* rec = makeRecord(i, i);
			list.addElement(rec);

			cache->addUpdatedRecord(table, rec);
		}

		int i = 0;
		UpdatedRecordCursor* cursor = cache->getUpdatedRecordCursor(table); __STP(cursor);
		while(cursor->hasNext()){
			const CdbRecord* crec = cursor->next();

			CdbRecord* rec = list.get(i++);

			CHECK(crec->getOid()->equals(rec->getOid()));
		}
	}
}
