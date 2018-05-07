/*
 * TestExecutor.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTEXECUTOR_H_
#define DEBUG_TESTEXECUTOR_H_

namespace alinous {

class TestExecutor {
public:
	TestExecutor();
	virtual ~TestExecutor();
};

extern TestExecutor testExecInst;


} /* namespace alinous */

#endif /* DEBUG_TESTEXECUTOR_H_ */
