/*
 * test_test.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "debug/t_macros.h"


using namespace alinous;

TEST_GROUP(test_test){
	TEST_SETUP{}
	TEST_TEARDOWN{}
};

TEST(test_test, test01){
	int val = 10;

	CHECK(val == 10);
}


