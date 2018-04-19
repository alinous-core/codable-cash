/*
 * TestSetup.cpp
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#include "TestSetup.h"

#include "base/UnicodeString.h"
#include "base_io/File.h"

#include "charsets/CharsetManager.h"

#include "CppUTest/CommandLineTestRunner.h"

namespace alinous {

TestSetup::TestSetup() {
	UnicodeString path(prog);
	this->baseDir = new File(&path);

}

TestSetup::~TestSetup() {
	delete this->baseDir;
}

void TestSetup::setup() {
	UtestShell *cur = UtestShell::getCurrent();

	const SimpleString group = cur->getGroup();
	const SimpleString name = cur->getName();

	const char* c_group = name.asCharString();
	const char* c_name = name.asCharString();



}
void TestSetup::teardown() {
	CharsetManager::closeInstance();
}

} /* namespace alinous */
