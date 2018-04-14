/*
 * test_hashmap.cpp
 *
 *  Created on: 2018/04/14
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"

#include "base/HashMap.h"
#include "base/UnicodeString.h"

using namespace alinous;


TEST_GROUP(HashMapKeySetTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(HashMapKeySetTestGroup, construct){
	HashMapKeySet<UnicodeString, UnicodeString>* set = new HashMapKeySet<UnicodeString, UnicodeString>();

	delete set;
}


