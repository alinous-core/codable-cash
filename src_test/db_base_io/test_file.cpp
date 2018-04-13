/*
 * test_file.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/File.h"

using namespace alinous;


TEST_GROUP(FileTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(FileTestGroup, test01){
	File* file = new File();

	delete file;
}


