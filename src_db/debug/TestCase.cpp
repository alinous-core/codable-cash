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
	this->file = file;
	this->line = line;

	this->setup->setNames(group->getName(), this->name);

	group->addTestCase(this->name, this);
}

TestCase::~TestCase() noexcept {
	delete this->name;
	delete this->setup;
}

void TestCase::doTest() {

	try{
		this->setup->setup();
	}catch(...){

	}
	try{
		testBody();
	}catch(...){

	}

	try{
		this->setup->teardown();
	}
	catch(...){

	}
}

} /* namespace alinous */
