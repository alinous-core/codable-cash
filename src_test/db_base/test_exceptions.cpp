/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "base/exceptions.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(ExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};



TEST(ExceptionsTestGroup, ex){
	Exception* ex = new Exception(__FILE__, __LINE__);
	delete ex;
}

TEST(ExceptionsTestGroup, test01){
	testException<NumberFormatException>();
	testException<IllegalArgumentException>();
}
