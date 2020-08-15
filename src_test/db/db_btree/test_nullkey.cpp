/*
 * test_nullkey.cpp
 *
 *  Created on: 2020/08/15
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "btreekey/NullKey.h"

#include "base_io/ByteBuffer.h"

#include "btreekey/BtreeKeyFactory.h"
#include <cstdint>
using namespace alinous;

TEST_GROUP(TestNullKeyGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

static bool checkBinary(ByteBuffer* buff);

bool checkBinary(ByteBuffer* buff){
	int lastSize = buff->capacity();

	buff->position(0);

	BtreeKeyFactory factory;
	uint32_t keyType = buff->getInt();
	AbstractBtreeKey* key = factory.fromBinary(keyType, buff); __STP(key);

	/// CodeElement* element = CodeElement::createFromBinary(buff); __STP(element);

	int size = key->binarySize();
	if(lastSize != size){
		return false;
	}

	ByteBuffer* buff2 = ByteBuffer::allocateWithEndian(size, true); __STP(buff2);
	key->toBinary(buff2);

	if(buff2->position() != size){
		return false;
	}

	return Mem::memcmp(buff->array(), buff2->array(), size) == 0;
}

TEST(TestNullKeyGroup, case01){
	NullKey nullkey;

	int size = nullkey.binarySize();
	ByteBuffer* buff = ByteBuffer::allocateWithEndian(size, true); __STP(buff);

	nullkey.toBinary(buff);

	checkBinary(buff);
}
