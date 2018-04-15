/*
 * test_integer.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"

#include "base/Integer.h"

using namespace alinous;

TEST_GROUP(IntegerTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}
};

TEST(IntegerTestGroup, construct){
	Integer* value = new Integer(100);

	delete value;
}


