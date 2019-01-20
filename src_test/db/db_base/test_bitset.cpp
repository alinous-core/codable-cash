/*
 * test_bitset.cpp
 *
 *  Created on: 2018/04/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/RawBitSet.h"

using namespace alinous;

TEST_GROUP(BitsetTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(BitsetTestGroup, test01){
	RawBitSet bs(10);

	bs.set(2);
	bs.set(4);
	bs.set(6);
	bs.set(1100);

	int pos = 0;

	int count = 0;
	while(pos >= 0){
		pos = bs.nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 4);

	bs.clear(4);
	bs.clear(2000);
	pos = 0;
	count = 0;
	while(pos >= 0){
		pos = bs.nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 3);

	bs.clear();
	pos = 0;
	count = 0;
	while(pos >= 0){
		pos = bs.nextSetBit(pos);
		if(pos < 0){
			break;
		}
		count++;
		pos++;
	}
	CHECK(count == 0);
}

TEST(BitsetTestGroup, test02){
	RawBitSet bs(1024);

	bs.set(400);
	bs.clear(400);

	CHECK(bs.nextSetBit(0) < 0);
}

TEST(BitsetTestGroup, test03){
	RawBitSet bs(64);

	bs.clear(5);
	bs.set(5);

	for(int i = 0; i != 64; ++i){
		int pos = bs.nextSetBit(i);

		if(i <= 5){
			CHECK(pos == 5);
		}
		else{
			CHECK(pos < 0);
		}
	}


}

