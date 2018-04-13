/*
 * test_arraylist.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */


#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"

#include "base/ArrayList.h"

using namespace alinous;

class dummyInt {
public:
	dummyInt() : value(0){
	}
	dummyInt(int i) : value(i){
	}

	int value;
};

TEST_GROUP(ArrayListTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(ArrayListTestGroup, test01){
	ArrayList<dummyInt> ar;

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test02){
	ArrayList<dummyInt> ar;

	ar.addElement(new dummyInt(1));

	CHECK(ar.size() == 1);

	int size = ar.size();
	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		delete ptr;
	}
}

TEST(ArrayListTestGroup, test03){
	ArrayList<dummyInt> ar;

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		CHECK(ptr->value == i);

		delete ptr;
	}
}

TEST(ArrayListTestGroup, test05){
	ArrayList<dummyInt> ar(1);

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test06){
	ArrayList<dummyInt> ar(8);

	CHECK(ar.size() == 0);
}

TEST(ArrayListTestGroup, test07){
	ArrayList<dummyInt> ar(8);

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.get(i);
		CHECK(ptr->value == i);

		delete ptr;
	}
}

TEST(ArrayListTestGroup, test08){
	ArrayList<dummyInt> ar(8);

	int maxLoop = 100;
	for(int i = 0; i != maxLoop; ++i){
		ar.addElement(new dummyInt(i));
	}

	int size = ar.size();
	CHECK(ar.size() == maxLoop);

	for(int i = 0; i != size; ++i){
		dummyInt* ptr = ar.remove(0);
		CHECK(ptr->value == i);

		delete ptr;
	}
}


