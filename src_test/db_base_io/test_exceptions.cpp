/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */



#include "test_utils/t_macros.h"

#include "base_io/exceptions.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(BaseExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(BaseExceptionsTestGroup, ex){
	Exception* ex = new Exception(__FILE__, __LINE__);
	delete ex;
}

TEST(BaseExceptionsTestGroup, test01){
	testException<BufferUnderflowException>();
	testException<BufferOverflowException>();
}
