/*
 * TestGroup.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "test_utils/TestGroup.h"
#include "test_utils/TestExecutor.h"
#include "test_utils/TestCase.h"
#include "test_utils/TestEnv.h"
#include "test_utils/TestParams.h"
#include "base/UnicodeString.h"
#include "base/HashMap.h"

namespace alinous {

TestGroup::TestGroup(const wchar_t* groupName, const char* file, int line) noexcept {
	this->groupName = new UnicodeString(groupName);
	this->tests = new HashMap<UnicodeString, TestCase>();

	TestExecutor::get()->addGroup(this->groupName, this);
}

TestGroup::~TestGroup() noexcept {
	delete this->groupName;
	delete this->tests;
}

void TestGroup::addTestCase(UnicodeString* name, TestCase* testCase) noexcept {
	this->tests->put(name, testCase);
}

void TestGroup::init(const char* prog) noexcept {
	auto it = this->tests->keySet()->iterator();

	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestCase* testCase = this->tests->get(key);

		testCase->getEnv()->init(prog);
	}

	delete it;
}

void TestGroup::execute(TestParams* params) {
	auto it = this->tests->keySet()->iterator();

	while(it->hasNext()){
		const UnicodeString* key = it->next();

		TestCase* testCase = this->tests->get(key);
		try{
			testCase->doTest(params);
		}
		catch(...){

		}
	}

	delete it;
}

UnicodeString* TestGroup::getName() const noexcept{
	return this->groupName;
}

} /* namespace alinous */


