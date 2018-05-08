/*
 * TestCase.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestCase.h"
#include "debug/TestGroup.h"
#include "debug/TestGroupActions.h"
#include "base/UnicodeString.h"

namespace alinous {

TestCase::TestCase(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) noexcept {
	this->group = group;
	this->name = new UnicodeString(name);
	this->setup = setup;

	group->addTestCase(this->name, this);
}

TestCase::~TestCase() noexcept {
	delete this->name;
	delete this->setup;
}

} /* namespace alinous */
