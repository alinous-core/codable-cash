/*
 * TestEnv.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/TestEnv.h"
#include "test_utils/TestCase.h"
#include "test_utils/TestGroup.h"
#include "test_utils/TestGroupActions.h"

#include "base_io/File.h"
#include "base/UnicodeString.h"
#include "base/StackRelease.h"

namespace alinous {


const UnicodeString* TestEnv::TEST_SEG() {
	static UnicodeString str(L"test_out");
	return &str;
}


TestEnv::TestEnv(TestCase* testCase) {
	this->testCase = testCase;
	this->baseDir = nullptr;
	this->projectRoot = nullptr;
}

void TestEnv::init(const char* prog) noexcept {
	UnicodeString path(prog);
	File progFile(&path);

	File* dir = progFile.getDirectory();

	this->baseDir = dir->get(TEST_SEG());

	File* tmp = dir->get(L"..");
	UnicodeString* rootPath = tmp->getAbsolutePath();

	this->projectRoot = new File(rootPath);

	delete tmp;
	delete rootPath;
	delete dir;
}


TestEnv::~TestEnv() {
	delete this->baseDir;
}

void TestEnv::setup() {
	File *groupBase = this->baseDir->get(this->testCase->getGroup()->getName());
	File *testCaseBase = groupBase->get(this->testCase->getName());
	StackMultipleRelease<File> r_files;
	r_files.add(groupBase);
	r_files.add(testCaseBase);

	groupBase->mkdirs();

	testCaseBase->deleteDir();

	testCaseBase->mkdirs();
}

void TestEnv::teardown() {
}

File TestEnv::testCaseDir() {
	File *groupBase = this->baseDir->get(this->testCase->getGroup()->getName());
	File *testCaseBase = groupBase->get(this->testCase->getName());
	StackMultipleRelease<File> r_files;
	r_files.add(groupBase);
	r_files.add(testCaseBase);

	return *testCaseBase;
}



} /* namespace alinous */
