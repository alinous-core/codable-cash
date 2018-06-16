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

#include <stdlib.h>


using namespace alinous;

TEST_GROUP(TestLongRangeGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

static void regBitset(RawBitSet* bitset, uint64_t min, uint64_t max){
	for(uint64_t i = min; i <= max; ++i){
		bitset->set((uint32_t)i);
	}
}

static void addRange(RawBitSet* bitset, LongRangeList* list, uint64_t min, uint64_t max){
	regBitset(bitset, min, max);
	list->addRange(min, max);
}


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
	list.assertList();
}

TEST(TestLongRangeGroup, emptyIterator){
	LongRangeList list;

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
	}
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
	list.assertList();
}

TEST(TestLongRangeGroup, addSimpleRangeIncluded){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 10, 15);
	addRange(&bitset, &list, 11, 13);

	int pos = bitset.nextSetBit(0);

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == pos)

		pos = bitset.nextSetBit(pos + 1);
	}
	CHECK(pos < 0);
	list.assertList();
}

TEST(TestLongRangeGroup, addSimpleRangeLowJoin){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 10, 15);
	addRange(&bitset, &list, 16, 17);

	int pos = bitset.nextSetBit(0);

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == pos)

		pos = bitset.nextSetBit(pos + 1);
	}
	CHECK(pos < 0);
	list.assertList();
}

TEST(TestLongRangeGroup, addSimpleRangeHighJoin){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 10, 15);
	addRange(&bitset, &list, 8, 9);

	int pos = bitset.nextSetBit(0);

	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == pos)

		pos = bitset.nextSetBit(pos + 1);
	}
	CHECK(pos < 0);

	list.assertList();
}


TEST(TestLongRangeGroup, addSimpleIncludes){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 15);
	list.assertList();

	addRange(&bitset, &list, 9, 16);
	list.assertList();

	int pos = bitset.nextSetBit(0);
	_ST(LongRangeIterator, it, list.iterator())
	while(it->hasNext()){
		uint64_t val = it->next();
		CHECK(val == pos)

		pos = bitset.nextSetBit(pos + 1);
	}
	CHECK(pos < 0);

	list.assertList();
}

TEST(TestLongRangeGroup, addSimpleIncludes02){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 15);
	list.assertList();

	addRange(&bitset, &list, 1, 6);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
	}

	addRange(&bitset, &list, 3, 8);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}


TEST(TestLongRangeGroup, addSinleRange){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 12);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}

TEST(TestLongRangeGroup, addSinleRange02){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 12);
	list.assertList();

	addRange(&bitset, &list, 13, 13);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}


TEST(TestLongRangeGroup, addSinleRange03){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 12);
	list.assertList();

	addRange(&bitset, &list, 13, 13);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}

TEST(TestLongRangeGroup, addSinleRange04){
	RawBitSet bitset(128);

	LongRangeList list;

	addRange(&bitset, &list, 8, 10);
	list.assertList();

	addRange(&bitset, &list, 12, 12);
	list.assertList();

	addRange(&bitset, &list, 13, 13);
	list.assertList();

	addRange(&bitset, &list, 8, 13);
	list.assertList();

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}


static void randomAdd(RawBitSet* bitset, LongRangeList* list){
	uint64_t mod = 1000;
	uint64_t mod_width = 100;

	uint64_t min = 1 + (rand() % mod);
	uint64_t max = min + (rand() % mod);

	addRange(bitset, list, min, max);
	list->assertList();
}

TEST(TestLongRangeGroup, addRamdom){
	RawBitSet bitset(128);
	LongRangeList list;

	for(int i = 0; i != 10000; ++i){
		randomAdd(&bitset, &list);
	}

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		while(it->hasNext()){
			uint64_t val = it->next();
			CHECK(val == pos)

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(pos < 0);
		list.assertList();
	}
}




