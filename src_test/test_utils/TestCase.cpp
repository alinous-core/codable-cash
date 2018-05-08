/*
 * TestCase.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "test_utils/TestCase.h"
#include "test_utils/TestGroup.h"
#include "test_utils/TestGroupActions.h"
#include "test_utils/Check.h"
#include "test_utils/TestEnv.h"
#include "test_utils/TestParams.h"
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

void TestCase::doTest(TestParams* params) {
	const char* result = "OK";
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

	if(params->isV()){
		printf("  %ls ... %s\n", this->name->towString(), result);
	}
	else{
		printf(".");
	}
}

Check* TestCase::addCheck(Check* check) noexcept {
	this->checks->addElement(check);
	return check;
}


const TestGroup* TestCase::getGroup() const noexcept {
	return this->group;
}
TestEnv* TestCase::getEnv() noexcept {
	return this->env;
}
const UnicodeString* TestCase::getName() const noexcept {
	return this->name;
}
} /* namespace alinous */

