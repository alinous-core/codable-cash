/*
 * test_file_stream.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */


#include "CppUTest/CommandLineTestRunner.h"
#include "test_utils/TestSetup.h"

using namespace alinous;


TEST_GROUP(FileStreamTestGroup) {
	TestSetup testenv;

	TEST_SETUP() {
		testenv.setup();
	}
	TEST_TEARDOWN() {
		testenv.teardown();
	}

};

TEST(FileStreamTestGroup, test01){

}
