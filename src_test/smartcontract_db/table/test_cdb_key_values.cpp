/*
 * test_cdb_key_values.cpp
 *
 *  Created on: 2020/05/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base_io/File.h"
#include "base/StackRelease.h"

#include "engine/CodableDatabase.h"

#include "trx/transaction/CdbTransaction.h"

#include "engine/CdbException.h"
#include "engine/CdbBinaryObject.h"

#include "base_io/ByteBuffer.h"

#include "schema_table/table_record/CdbKeyFactory.h"
#include <cstdint>

#include "btreekey/InfinityKey.h"

#include "schema_table/table_record_key/CdbByteKey.h"
#include "schema_table/table_record_key/CdbShortKey.h"
#include "schema_table/table_record_key/CdbIntKey.h"
#include "schema_table/table_record_key/CdbLongKey.h"
#include "schema_table/table_record_key/CdbStringKey.h"
#include "schema_table/table_record_key/CdbRecordKey.h"

#include "btreekey/NullKey.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCdbKeyValuesGroup) {
	TEST_SETUP() {
	}
	TEST_TEARDOWN() {
	}
};

TEST(TestCdbKeyValuesGroup, CdbByteKey){
	CdbByteKey key;
	CdbByteKey* key2 = dynamic_cast<CdbByteKey*>(key.clone()); __STP(key2);

	CHECK(key.compareTo(key2) == 0)

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbShortKey){
	CdbShortKey key;
	CdbShortKey* key2 = dynamic_cast<CdbShortKey*>(key.clone()); __STP(key2);

	CHECK(key.compareTo(key2) == 0)

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbIntKey){
	CdbIntKey key;
	CdbIntKey* key2 = dynamic_cast<CdbIntKey*>(key.clone()); __STP(key2);

	CHECK(key.compareTo(key2) == 0)

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbLongKey){
	CdbLongKey key;
	CdbLongKey* key2 = dynamic_cast<CdbLongKey*>(key.clone()); __STP(key2);

	CHECK(key.compareTo(key2) == 0)

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbStringKey){
	UnicodeString hello(L"hello");
	CdbStringKey key(&hello);
	CdbStringKey* key2 = dynamic_cast<CdbStringKey*>(key.clone()); __STP(key2);

	CHECK(key.compareTo(key2) == 0)

	int size = key.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key.toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbRecordKey01){
	CdbRecordKey* key = new CdbRecordKey(); __STP(key);
	key->addKey(nullptr);

	CdbRecordKey* key2 = dynamic_cast<CdbRecordKey*>(key->clone()); __STP(key2);

	CHECK(key->compareTo(key2) == 0)

	int size = key->binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);
	key->toBinary(buff);

	buff->position(0);

	CdbKeyFactory factory;

	uint32_t type = buff->getInt();
	AbstractBtreeKey* retKey = factory.fromBinary(type, buff);__STP(retKey);

	int cmpResult = retKey->compareTo(key2);
	CHECK(cmpResult == 0);

	InfinityKey inf;
	cmpResult = retKey->compareTo(&inf);
	CHECK(cmpResult < 0);

	NullKey nullkey;
	cmpResult = retKey->compareTo(&nullkey);
	CHECK(cmpResult > 0);
}

TEST(TestCdbKeyValuesGroup, CdbRecordKey02){
	CdbRecordKey* key = new CdbRecordKey(); __STP(key);
	key->addKey(new CdbIntKey(1));

	CdbRecordKey* key2 = new CdbRecordKey(); __STP(key2);
	key2->addKey(new CdbIntKey(2));

	CHECK(key->compareTo(key2) < 0)
}

