/*
 * TestSetup.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTSETUP_H_
#define TEST_UTILS_TESTSETUP_H_

extern const char* prog;

namespace alinous {

class TestSetup {
public:
	TestSetup();
	virtual ~TestSetup();
};

} /* namespace alinous */

#endif /* TEST_UTILS_TESTSETUP_H_ */
