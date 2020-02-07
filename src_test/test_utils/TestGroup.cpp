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
#include "test_utils/TestSummary.h"
#include "base/UnicodeString.h"
#include "base/HashMap.h"

#include "base_io_stream/Writer.h"
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

		if(params->skipTest(key)){
			continue;
		}

		TestCase* testCase = this->tests->get(key);
		try{
			testCase->doTest(params);
		}
		catch(...){

		}

		ErrorPointManager* errmgr = ErrorPointManager::getInstance();
		errmgr->clear();
	}
	delete it;
}

void TestGroup::summaryTest(TestSummary* summary) noexcept {
	auto it = this->tests->keySet()->iterator();

	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestCase* testCase = this->tests->get(key);
		summary->analyze(testCase);
	}

	delete it;
}

UnicodeString* TestGroup::getName() const noexcept{
	return this->groupName;
}

void TestGroup::exportJUnitXML(Writer* writer) const {
	TestSummary summary;
	auto it = this->tests->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestCase* testCase = this->tests->get(key);
		summary.analyze(testCase);
	}

	delete it;

	UnicodeString testSuite(L"  <testsuite failures=\"");
	testSuite.append(summary.getFailedTest()).append(L"\" hostname=\"localhost\" name=\"")
			.append(this->groupName).append(L"\" tests=\"").append(summary.getTotalTests()).append(L"\"").append(L">\n");
	writer->write(&testSuite);

	it = this->tests->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestCase* testCase = this->tests->get(key);

		testCase->exportJUnitXML(writer);
	}
	delete it;

	writer->write(L"  </testsuite>\n");
}

} /* namespace alinous */


