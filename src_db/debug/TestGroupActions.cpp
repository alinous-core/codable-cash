/*
 * TestGroupSetup.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "debug/TestGroupActions.h"
#include "base/UnicodeString.h"

namespace alinous {

alinous::TestGroupActions::TestGroupActions() {
	this->testCaseName = nullptr;
	this->testGroupName = nullptr;
}

alinous::TestGroupActions::~TestGroupActions() {
	delete this->testCaseName;
	delete this->testGroupName;
}


void alinous::TestGroupActions::setup() {
}

void alinous::TestGroupActions::teardown() {
}

} /* namespace alinous */

void alinous::TestGroupActions::setNames(UnicodeString* testGroupName, UnicodeString* testCaseName) noexcept {
	this->testCaseName = new UnicodeString(testCaseName);
	this->testGroupName = new UnicodeString(testGroupName);
}
