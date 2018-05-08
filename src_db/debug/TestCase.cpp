/*
 * TestCase.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestCase.h"
#include "debug/TestGroup.h"
#include "debug/TestGroupActions.h"
#include "debug/Check.h"
#include "debug/TestEnv.h"
#include "base/UnicodeString.h"

namespace alinous {

TestCase::TestCase(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) noexcept {
	this->group = group;
	this->name = new UnicodeString(name);
	this->setup = setup;
	this->file = new UnicodeString(file);
	this->line = line;
	this->checks = new ArrayList<Check>();
	this->env = new TestEnv(this);

	this->setup->setNames(group->getName(), this->name);
	this->setup->setTestEnv(this->env);

	group->addTestCase(this->name, this);
}

TestCase::~TestCase() noexcept {
	delete this->name;
	delete this->setup;
	delete this->file;

	this->checks->deleteElements();
	delete this->checks;
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

Check* TestCase::addCheck(Check* check) noexcept {
	this->checks->addElement(check);
	return check;
}


const TestGroup* TestCase::getGroup() const noexcept {
	return this->group;
}


} /* namespace alinous */
