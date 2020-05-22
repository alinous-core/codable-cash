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

#include "transaction/CdbTransaction.h"

#include "engine/CdbException.h"
#include "engine/CdbBinaryObject.h"

#include "table_record_key/CdbByteKey.h"

#include "base_io/ByteBuffer.h"

#include "table_record/CdbKeyFactory.h"
#include <cstdint>

#include "btreekey/InfinityKey.h"

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
}


