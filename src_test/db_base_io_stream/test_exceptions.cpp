/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"

#include "base_io_stream/exceptions.h"
#include "base/UnicodeString.h"

#include "test_utils/TestSetup.h"

using namespace alinous;

TEST_GROUP(FileExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(FileExceptionsTestGroup, test01){
	testException<FileOpenException>();
	testException<FileIOException>();
}

