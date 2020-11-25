/*
 * test_delete_trx_cache.cpp
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
#include "trx/scan/transaction_update_cache/DeletedRecordsOidsCursor.h"

#include "smartcontract_db/toolkit/TestDbSchema01.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestDeleteTrxCacheGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestDeleteTrxCacheGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		CodableDatabase* db = tester.getDatabase();

		SchemaManager* schema = db->getSchemaManager();
		CdbTable* table = schema->getTable(L"public", L"test_table");

		CdbTransaction* trx = db->newTransaction(); __STP(trx);
		TransactionUpdateCache* cache = trx->getUpdateCache();

		CdbOid record01(10);
		cache->addDeletedRecord(table, &record01);

		bool bl = cache->isDeleted(table, &record01);
		CHECK(bl);
	}
}

TEST(TestDeleteTrxCacheGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init();

	{
		CodableDatabase* db = tester.getDatabase();

		SchemaManager* schema = db->getSchemaManager();
		CdbTable* table = schema->getTable(L"public", L"test_table");

		CdbTransaction* trx = db->newTransaction(); __STP(trx);
		TransactionUpdateCache* cache = trx->getUpdateCache();

		RawArrayPrimitive<uint64_t> list(10);

		int maxLoop = 10;
		for(int i = 0; i != maxLoop; ++i){
			CdbOid record01(i);
			cache->addDeletedRecord(table, &record01);

			list.addElement(i);
		}

		int count = 0;
		DeletedRecordsOidsCursor* cursor = cache->getDeletedRecordsOidsCursor(table); __STP(cursor);
		while(cursor->hasNext()){
			const CdbOid* o = cursor->next();

			uint64_t v = o->getOidValue();
			uint64_t ans = list.get(count);

			CHECK(v == ans);

			count++;
		}
	}
}
