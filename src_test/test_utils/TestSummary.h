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

class TestSummary {
public:
	TestSummary();
	virtual ~TestSummary();

private:
	int totalTests;
	int successedTest;
	int failedTest;
	int successedcheck;
	int failedcheck;

	// failed

};

} /* namespace alinous */

#endif /* TEST_UTILS_TESTSUMMARY_H_ */
