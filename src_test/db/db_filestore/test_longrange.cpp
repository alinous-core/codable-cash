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

	int r1 = rand();
	int r2 = rand();

	r1 = abs(r1);
	r2 = abs(r2);

	uint64_t min = 1 + (r1 % mod);
	uint64_t max = min + (r2 % mod);

	//printf("addRange(&bitset, &list, %ld, %ld);\n", min, max);

	addRange(bitset, list, min, max);
	list->assertList();
}

TEST(TestLongRangeGroup, addRamdom){
	RawBitSet bitset(128);
	LongRangeList list;

	for(int i = 0; i != 100; ++i){
		randomAdd(&bitset, &list);
	}

	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		bool checked = true;
		while(it->hasNext()){
			uint64_t val = it->next();
			if(val != pos){
				checked = false;
				break;
			}

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(checked == true);
		CHECK(pos < 0);
		list.assertList();
	}
}

static void iterateAddRandom(RawBitSet* bitset, LongRangeList* list){
	for(int i = 0; i != 100; ++i){
		list->assertList();
		randomAdd(bitset, list);
	}
}

TEST(TestLongRangeGroup, addRamdom2){
	for(int i = 0; i != 200; ++i){
		RawBitSet bitset(128);
		LongRangeList list;
		//printf("--------------\n");

		iterateAddRandom(&bitset, &list);

		{
			int pos = bitset.nextSetBit(0);
			_ST(LongRangeIterator, it, list.iterator())
			bool checked = true;
			while(it->hasNext()){
				uint64_t val = it->next();
				if(val != pos){
					checked = false;
					break;
				}

				pos = bitset.nextSetBit(pos + 1);
			}
			CHECK(checked == true);
			CHECK(pos < 0);
			list.assertList();
		}
	}
}

TEST(TestLongRangeGroup, addRamdomErrorCase){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 458, 1395);
	addRange(&bitset, &list, 693, 853);
	addRange(&bitset, &list, 584, 1462);
	addRange(&bitset, &list, 583, 750);
	addRange(&bitset, &list, 495, 707);
	addRange(&bitset, &list, 642, 1212);
	addRange(&bitset, &list, 620, 1141);
	addRange(&bitset, &list, 418, 536);
	addRange(&bitset, &list, 325, 363);
	addRange(&bitset, &list, 974, 988);
	addRange(&bitset, &list, 54, 314);
	addRange(&bitset, &list, 744, 1476);
	addRange(&bitset, &list, 726, 964);
	addRange(&bitset, &list, 294, 1008);


	{
		int pos = bitset.nextSetBit(0);
		_ST(LongRangeIterator, it, list.iterator())
		bool checked = true;
		while(it->hasNext()){
			uint64_t val = it->next();
			if(val != pos){
				checked = false;
				break;
			}

			pos = bitset.nextSetBit(pos + 1);
		}
		CHECK(checked == true);
		CHECK(pos < 0);
		list.assertList();
	}
}


static void removeBitset(RawBitSet* bitset, uint64_t min, uint64_t max){
	for(uint64_t i = min; i <= max; ++i){
		bitset->clear((uint32_t)i);
	}
}

static void removeRange(RawBitSet* bitset, LongRangeList* list, uint64_t min, uint64_t max){
	assert(min <= max);

	removeBitset(bitset, min, max);
	list->removeRange(min, max);
}


TEST(TestLongRangeGroup, remove01){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	removeRange(&bitset, &list, 7, 9);

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


TEST(TestLongRangeGroup, remove02){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	removeRange(&bitset, &list, 5, 10);


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


TEST(TestLongRangeGroup, remove03){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	removeRange(&bitset, &list, 5, 8);


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


TEST(TestLongRangeGroup, remove04){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	removeRange(&bitset, &list, 6, 10);


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


TEST(TestLongRangeGroup, remove05){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	addRange(&bitset, &list, 15, 20);
	list.assertList();

	addRange(&bitset, &list, 23, 26);
	list.assertList();

	removeRange(&bitset, &list, 6, 23);


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


TEST(TestLongRangeGroup, remove06){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	addRange(&bitset, &list, 15, 20);
	list.assertList();

	addRange(&bitset, &list, 23, 26);
	list.assertList();

	removeRange(&bitset, &list, 5, 26);


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


TEST(TestLongRangeGroup, remove07){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	addRange(&bitset, &list, 15, 20);
	list.assertList();

	addRange(&bitset, &list, 23, 26);
	list.assertList();

	removeRange(&bitset, &list, 6, 25);


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


TEST(TestLongRangeGroup, remove08){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	addRange(&bitset, &list, 15, 20);
	list.assertList();

	addRange(&bitset, &list, 23, 26);
	list.assertList();

	removeRange(&bitset, &list, 0, 100);


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


TEST(TestLongRangeGroup, remove09){
	RawBitSet bitset(128);
	LongRangeList list;

	addRange(&bitset, &list, 5, 10);
	list.assertList();

	addRange(&bitset, &list, 15, 20);
	list.assertList();

	addRange(&bitset, &list, 23, 26);
	list.assertList();

	removeRange(&bitset, &list, 11, 21);


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


TEST(TestLongRangeGroup, equals01){
	LongRangeList list;
	list.addRange(10, 12);

	LongRangeList list2;
	list2.addRange(10, 12);

	bool result = list.equals(&list2);
	CHECK(result)
}

TEST(TestLongRangeGroup, equals02){
	LongRangeList list;
	list.addRange(10, 12);

	LongRangeList list2;
	list2.addRange(10, 13);

	bool result = list.equals(&list2);
	CHECK(!result)
}

TEST(TestLongRangeGroup, equals03){
	LongRangeList list;
	list.addRange(10, 12);

	LongRangeList list2;
	list.addRange(10, 12);
	list.addRange(14, 14);

	bool result = list.equals(&list2);
	CHECK(!result)
}

TEST(TestLongRangeGroup, firstEmpty01){
	LongRangeList list;
	list.addRange(10, 12);

	uint64_t pos = list.firstEmpty();
	CHECK(pos == 0)
}

