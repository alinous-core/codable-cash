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

