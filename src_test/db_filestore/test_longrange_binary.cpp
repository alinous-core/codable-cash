/*
 * test_longrange_binary.cpp
 *
 *  Created on: 2018/11/11
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "filestore/LongRangeList.h"
#include "filestore/LongRangeIterator.h"
#include "base/StackRelease.h"
#include "base/RawBitSet.h"

#include "base_io/ByteBuffer.h"

#include <stdlib.h>


using namespace alinous;

TEST_GROUP(TestLongRangeBinaryGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};


TEST(TestLongRangeBinaryGroup, nodata){
	LongRangeList list;

	int size = list.binarySize();
	CHECK(size == 4)
}

TEST(TestLongRangeBinaryGroup, oneRange){
	LongRangeList list;

	list.addRange(10, 12);

	int size = list.binarySize();
	CHECK(size == 4 + 16)
}

TEST(TestLongRangeBinaryGroup, oneRangeBinary){
	LongRangeList list;
	list.addRange(10, 12);

	int size = list.binarySize();
	ByteBuffer* buffer = ByteBuffer::allocate(size);
	StackRelease<ByteBuffer> _st_buffer(buffer);

	list.toBinary(buffer);

	buffer->position(0);
	LongRangeList* binList = LongRangeList::fromBinary(buffer);
	StackRelease<LongRangeList> _st_binList(binList);

	bool result = list.equals(binList);
	CHECK(result);
}

