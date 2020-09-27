/*
 * test_oid_cache.cpp
 *
 *  Created on: 2020/09/24
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "random_access_file/DiskCacheManager.h"

#include "transaction_cache/CdbSwapCacheFactory.h"
#include "transaction_cache/SingleKeyOidCache.h"

#include "btreekey/ULongKey.h"

#include "engine/CdbOid.h"

#include "table_record_key/CdbOidKey.h"
TEST_GROUP(TestOidCacheGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestOidCacheGroup, case01){
	File testCaseFolder = this->env->testCaseDir();
	File* tmpDir = testCaseFolder.get(L"tmp_cache"); __STP(tmpDir);

	DiskCacheManager diskCache;

	CdbSwapCacheFactory factory(tmpDir, &diskCache);
	factory.resetDir();

	SingleKeyOidCache* cache = factory.createSingleKeyOidCache(1024); __STP(cache);

	cache->removeFiles();
}

TEST(TestOidCacheGroup, memory01){
	File testCaseFolder = this->env->testCaseDir();
	File* tmpDir = testCaseFolder.get(L"tmp_cache"); __STP(tmpDir);

	DiskCacheManager diskCache;

	CdbSwapCacheFactory factory(tmpDir, &diskCache);
	factory.resetDir();

	SingleKeyOidCache* cache = factory.createSingleKeyOidCache(1024); __STP(cache);

	CdbOid oid(10);
	CdbOidKey key(&oid);

	cache->insert(&key, &oid);

	bool bl = cache->hasKey(&key);
	CHECK(bl);

	cache->removeFiles();
}

TEST(TestOidCacheGroup, memory02){
	File testCaseFolder = this->env->testCaseDir();
	File* tmpDir = testCaseFolder.get(L"tmp_cache"); __STP(tmpDir);

	DiskCacheManager diskCache;

	CdbSwapCacheFactory factory(tmpDir, &diskCache);
	factory.resetDir();

	SingleKeyOidCache* cache = factory.createSingleKeyOidCache(1024); __STP(cache);

	CdbOid oid(10);
	CdbOidKey key(&oid);

	cache->insert(&key, &oid);
	cache->insert(&key, &oid);

	bool bl = cache->hasKey(&key);
	CHECK(bl);

	cache->removeFiles();
}
