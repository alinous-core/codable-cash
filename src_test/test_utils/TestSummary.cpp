/*
 * TestSummary.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include <test_utils/TestSummary.h>

namespace alinous {

TestSummary::TestSummary() {
	this->totalTests = 0;
	this->successedTest = 0;
	this->failedTest = 0;
	this->successedcheck = 0;
	this->failedcheck = 0;

}

TestSummary::~TestSummary() {

}

} /* namespace alinous */
