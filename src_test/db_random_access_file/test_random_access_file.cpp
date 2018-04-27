/*
 * test_random_access_file.cpp
 *
 *  Created on: 2018/04/26
 *      Author: iizuka
 */

#include "CppUTest/CommandLineTestRunner.h"
#include "test_utils/TestSetup.h"

#include "random_access_file/RandomAccessFile.h"

using namespace alinous;


TEST_GROUP(RandomAccessFileTestGroup) {
	TestSetup testenv;

	TEST_SETUP() {
		testenv.setup();
	}
	TEST_TEARDOWN() {
		testenv.teardown();
	}
};

TEST(RandomAccessFileTestGroup, construct){
	File projectFolder = this->testenv.testCaseDir();

	UnicodeString mode(L"wr");

	UnicodeString name(L"out.bin");
	File* outFile = projectFolder.get(&name);
	StackRelease<File> r_outFile(outFile);

	RandomAccessFile file(outFile, nullptr);
	file.open();

}


