/*
 * test_oid_key.cpp
 *
 *  Created on: 2020/09/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CdbOid.h"

#include "schema_table/table_record_key/CdbOidKey.h"
#include "schema_table/table_record/CdbKeyFactory.h"

#include "btree/AbstractBtreeKey.h"

#include "btreekey/NullKey.h"
#include "btreekey/InfinityKey.h"

#include "base_io/ByteBuffer.h"


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

static bool checkBinary(ByteBuffer* buff);
bool checkBinary(ByteBuffer* buff){
	CdbKeyFactory factory;

	int lastSize = buff->capacity();

	buff->position(0);

	int32_t keytype = buff->getInt();
	AbstractBtreeKey* element = factory.fromBinary(keytype, buff); __STP(element);

	int size = element->binarySize();
	if(lastSize != size){
		return false;
	}

	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true); __STP(buff2);
	element->toBinary(buff2);

	if(buff2->position() != size){
		return false;
	}

	return Mem::memcmp(buff->array(), buff2->array(), size) == 0;
}

TEST(TestOidKeyGroup, binary01){
	CdbOid oid(1);
	CdbOidKey key(&oid);

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	bool result = checkBinary(buff);
	CHECK(result)
}

