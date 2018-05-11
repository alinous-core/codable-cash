/*
 * test_exceptions.cpp
 *
 *  Created on: 2018/04/25
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base_io_stream/exceptions.h"
#include "base/UnicodeString.h"

using namespace alinous;

TEST_GROUP(FileExceptionsTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};

TEST(FileExceptionsTestGroup, test01){
	testException<FileOpenException>();
	testException<FileIOException>();
}

