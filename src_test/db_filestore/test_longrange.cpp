/*
 * test_longrange.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "filestore/LongRangeList.h"

#include "base/StackRelease.h"

#include "filestore/LongRangeIterator.h"
using namespace alinous;

TEST_GROUP(TestLongRangeGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(TestLongRangeGroup, construct){
	LongRangeList list;
}

TEST(TestLongRangeGroup, addSimpleRange){
	LongRangeList list;

	list.addRange(10);

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == 10)
	}
}

TEST(TestLongRangeGroup, addSimpleRange02){
	LongRangeList list;

	list.addRange(10, 15);


	list.addRange(1, 2);

}
