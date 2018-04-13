/*
 * test_file.cpp
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"

using namespace alinous;


TEST_GROUP(FileTestGroup) {
	TEST_SETUP() {}
	TEST_TEARDOWN() {}

};


TEST(FileTestGroup, test01){
	UnicodeString path(L"testdir");
	File* file = new File(&path);

	delete file;
}


