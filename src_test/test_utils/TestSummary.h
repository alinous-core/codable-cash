/*
 * TestSummary.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTSUMMARY_H_
#define TEST_UTILS_TESTSUMMARY_H_

#include "base/HashMap.h"
#include "base/ArrayList.h"

namespace alinous {

class TestCase;
class UnicodeString;
class Check;

class TestSummary {
public:
	TestSummary() noexcept;
	virtual ~TestSummary() noexcept;

	void analyze(TestCase* testCase) noexcept;
	void echoSummary() const noexcept;

	int getFailedTest() const {
		return failedTest;
	}
	int getSuccessedTest() const {
		return successedTest;
	}
	int getTotalTests() const {
		return totalTests;
	}

	bool isSuccess() const noexcept;
private:
	ArrayList<TestCase>* getGroupCaseList(const UnicodeString* grp) noexcept;
	void analyzeChecks(ArrayList<Check>* checkList) noexcept;
	void echoFailureSummary() const noexcept;
private:
	int totalTests;
	int successedTest;
	int failedTest;
	int successedcheck;
	int failedcheck;

	// failed
	HashMap<UnicodeString, ArrayList<TestCase>>* failedTests;
};

} /* namespace alinous */

#endif /* TEST_UTILS_TESTSUMMARY_H_ */
