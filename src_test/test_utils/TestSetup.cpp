/*
 * TestSetup.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "TestSetup.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"
#include "base_io/File.h"

#include "charsets/CharsetManager.h"

#include "CppUTest/CommandLineTestRunner.h"

namespace alinous {

TestSetup::TestSetup() {
	UnicodeString path(prog);
	File progFile(&path);

	this->baseDir = progFile.getDirectory();

}

TestSetup::~TestSetup() {
	delete this->baseDir;
}

void TestSetup::setup() {
	UtestShell *cur = UtestShell::getCurrent();

	const SimpleString group = cur->getGroup();
	const SimpleString name = cur->getGroup();

	const char* c_group = group.asCharString();
	const char* c_name = name.asCharString();

	UnicodeString strGroup(c_group);
	UnicodeString strName(c_group);

	File *groupBase = this->baseDir->get(&strGroup);
	File *testCaseBase = this->baseDir->get(&strGroup);
	StackArrayRelease<File> r_files;
	r_files.add(groupBase);
	r_files.add(testCaseBase);

	groupBase->mkdirs();

	//testCaseBase->deleteDir();
	//testCaseBase->mkdirs();
}
void TestSetup::teardown() {
	CharsetManager::closeInstance();
}

} /* namespace alinous */
