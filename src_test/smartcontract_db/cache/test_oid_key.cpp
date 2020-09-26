/*
 * test_oid_key.cpp
 *
 *  Created on: 2020/09/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CdbOid.h"

#include "table_record_key/CdbOidKey.h"

#include "btree/AbstractBtreeKey.h"

#include "btreekey/NullKey.h"
#include "btreekey/InfinityKey.h"

using namespace codablecash;

TEST_GROUP(TestOidKeyGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

TEST(TestOidKeyGroup, case01){
	CdbOid oid(1);
	CdbOidKey key(&oid);

	AbstractBtreeKey* key2 = key.clone(); __STP(key2);

	int diff = key2->compareTo(&key);
	CHECK(diff == 0);
}

TEST(TestOidKeyGroup, case02){
	CdbOid oid(1);
	CdbOidKey key(&oid);

	NullKey nullkey;
	int diff = key.compareTo(&nullkey);
	CHECK(diff > 0);
}

TEST(TestOidKeyGroup, case03){
	CdbOid oid(1);
	CdbOidKey key(&oid);

	InfinityKey infkey;
	int diff = key.compareTo(&infkey);
	CHECK(diff < 0);
}
