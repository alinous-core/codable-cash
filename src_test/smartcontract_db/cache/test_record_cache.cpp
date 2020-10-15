/*
 * test_record_cache.cpp
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/RawArrayPrimitive.h"

#include "vm/VirtualMachine.h"

#include "random_access_file/DiskCacheManager.h"

#include "trx/transaction_cache/CdbSwapCacheFactory.h"
#include "trx/transaction_cache/SingleKeyOidCache.h"
#include "trx/transaction_cache/OidKeyRecordCache.h"

#include "btreekey/ULongKey.h"

#include "engine/CdbOid.h"
#include "engine/CdbException.h"

#include "schema_table/record/table_record/CdbRecord.h"

#include "schema_table/record/table_record_key/CdbOidKey.h"


TEST_GROUP(TestRecordCacheGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestRecordCacheGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* tmpDir = testCaseFolder.get(L"tmp_cache"); __STP(tmpDir);

	DiskCacheManager diskCache;

	CdbSwapCacheFactory factory(tmpDir, &diskCache);
	factory.resetDir();

	CdbRecord* record = new CdbRecord(); __STP(record);
	CdbOid oid(1);
	record->setOid(&oid);

	OidKeyRecordCache* cache = factory.createOidKeyRecordCache(100); __STP(cache);
	cache->insert(record);
}

TEST(TestRecordCacheGroup, case02){
	File testCaseFolder = this->env->testCaseDir();
	File* tmpDir = testCaseFolder.get(L"tmp_cache"); __STP(tmpDir);

	DiskCacheManager diskCache;

	CdbSwapCacheFactory factory(tmpDir, &diskCache);
	factory.resetDir();

	CdbRecord* record = new CdbRecord(); __STP(record);
	CdbOid oid(1);
	record->setOid(&oid);

	OidKeyRecordCache* cache = factory.createOidKeyRecordCache(100); __STP(cache);
	cache->insert(record);

	CdbException* ex = nullptr;
	try{
		cache->insert(record);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

