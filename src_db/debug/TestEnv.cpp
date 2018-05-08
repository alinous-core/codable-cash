/*
 * TestEnv.cpp
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#include "debug/TestEnv.h"
#include "debug/TestCase.h"
#include "debug/TestGroupActions.h"

namespace alinous {

TestEnv::TestEnv(TestCase* testCase) {
	this->testCase = testCase;

}

TestEnv::~TestEnv() {
}

} /* namespace alinous */
