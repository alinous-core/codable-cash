/*
 * TestEnv.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_TESTENV_H_
#define DEBUG_TESTENV_H_

namespace alinous {

class TestGroupActions;
class TestCase;

class TestEnv {
public:
	TestEnv(TestCase* testCase);
	virtual ~TestEnv();

protected:
	TestCase* testCase;
};

} /* namespace alinous */

#endif /* DEBUG_TESTENV_H_ */
