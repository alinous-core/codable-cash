/*
 * test_longrange.cpp
 *
 *  Created on: 2018/05/18
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "filestore/LongRangeList.h"
#include "filestore/LongRangeIterator.h"
#include "base/StackRelease.h"
#include "base/RawBitSet.h"


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

TEST(TestLongRangeGroup, emptyIterator){
	LongRangeList list;

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
	}
}

static void addRange(RawBitSet* bitset, LongRangeList* list, uint64_t min, uint64_t max){
	for(uint64_t i = min; i <= max; ++i){
		bitset->set((uint32_t)i);
	}
	list->addRange(min, max);
}


TEST(TestLongRangeGroup, addSimpleRange02){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 10, 15);
	addRange(&bitset, &list, 1, 2);

	int pos = bitset.nextSetBit(0);

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == pos)

		pos = bitset.nextSetBit(pos + 1);
	}
	CHECK(pos < 0);
}
