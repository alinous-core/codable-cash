/*
 * TestGroupSetup.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "test_utils/TestGroupActions.h"
#include "base/UnicodeString.h"

namespace alinous {

alinous::TestGroupActions::TestGroupActions() {
	this->testCaseName = nullptr;
	this->testGroupName = nullptr;
	this->env = nullptr;
}

alinous::TestGroupActions::~TestGroupActions() {
	delete this->testCaseName;
	delete this->testGroupName;
}


void alinous::TestGroupActions::setup() {
}

void alinous::TestGroupActions::teardown() {
}

void TestGroupActions::setNames(UnicodeString* testGroupName, UnicodeString* testCaseName) noexcept {
	this->testCaseName = new UnicodeString(testCaseName);
	this->testGroupName = new UnicodeString(testGroupName);
}

void TestGroupActions::setTestEnv(TestEnv* env) noexcept {
	this->env = env;
}

} /* namespace alinous */


