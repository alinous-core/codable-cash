/*
 * test_primitive_array.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/RawArrayPrimitive.h"

using namespace alinous;

TEST_GROUP(RawArrayPrimitiveTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(RawArrayPrimitiveTestGroup, test01){
	RawArrayPrimitive<int> ar(4);

	for(int i = 0; i != 1000; ++i){
		ar.addElement(i);
	}
}

TEST(RawArrayPrimitiveTestGroup, test02){
	RawArrayPrimitive<int> ar(4);

	for(int i = 0; i != 8; ++i){
		ar.addElement(i, 0);
	}

	int* p = ar.getRoot();
	CHECK(p[0] == 7);
	CHECK(p[1] == 6);
	CHECK(p[2] == 5);
	CHECK(p[3] == 4);
	CHECK(p[4] == 3);
	CHECK(p[5] == 2);
	CHECK(p[6] == 1);
	CHECK(p[7] == 0);

	ar.set(4, 0);
	CHECK(p[4] == 0);

	ar.addElement(0, 5);
	p = ar.getRoot();

	CHECK(p[5] == 0);
	CHECK(p[6] == 2);
	CHECK(p[7] == 1);
	CHECK(p[8] == 0);
}

TEST(RawArrayPrimitiveTestGroup, testRemove){
	RawArrayPrimitive<int> ar(4);

	for(int i = 0; i != 8; ++i){
		ar.addElement(i, 0);
	}

	ar.remove(4);

}

