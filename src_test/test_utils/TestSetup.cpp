/*
 * TestSetup.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "TestSetup.h"

#include "charsets/CharsetManager.h"

#include "CppUTest/CommandLineTestRunner.h"

namespace alinous {

UnicodeString TestSetup::TEST_SEG(L"test_out");

TestSetup::TestSetup() {
	UnicodeString path(prog);
	File progFile(&path);

	File* dir = progFile.getDirectory();


	this->baseDir = dir->get(&TEST_SEG);
	delete dir;

	// DEBUG:
	UnicodeString* abspath = this->baseDir->getAbsolutePath();
	const char* cpath = abspath->toCString();

	printf("\nPATH : %s\n", cpath);
	delete [] cpath;
	delete abspath;
}

TestSetup::~TestSetup() {
	delete this->baseDir;
}

void TestSetup::setup() {
	UtestShell *cur = UtestShell::getCurrent();

	const SimpleString group = cur->getGroup();
	const SimpleString name = cur->getName();

	const char* c_group = group.asCharString();
	const char* c_name = name.asCharString();

	UnicodeString strGroup(c_group);
	UnicodeString strName(c_name);

	File *groupBase = this->baseDir->get(&strGroup);
	File *testCaseBase = groupBase->get(&strName);
	StackMultipleRelease<File> r_files;
	r_files.add(groupBase);
	r_files.add(testCaseBase);

	groupBase->mkdirs();

	testCaseBase->deleteDir();
	testCaseBase->mkdirs();
}
void TestSetup::teardown() {
	clearStatics();
}

void TestSetup::clearStatics() {
	CharsetManager::closeInstance();
	ErrorPointManager::closeInstance();
}

File TestSetup::testCaseDir() {
	UtestShell *cur = UtestShell::getCurrent();

	const SimpleString group = cur->getGroup();
	const SimpleString name = cur->getName();

	const char* c_group = group.asCharString();
	const char* c_name = name.asCharString();

	UnicodeString strGroup(c_group);
	UnicodeString strName(c_name);

	File *groupBase = this->baseDir->get(&strGroup);
	File *testCaseBase = groupBase->get(&strName);
	StackMultipleRelease<File> r_files;
	r_files.add(groupBase);
	r_files.add(testCaseBase);

	return *testCaseBase;
}



} /* namespace alinous */
