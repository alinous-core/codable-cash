/*
 * TestCase.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTCASE_H_
#define DEBUG_TESTCASE_H_

namespace alinous {

class TestGroup;
class UnicodeString;

class TestCase {
public:
	TestCase(TestGroup* group, UnicodeString* name) noexcept;
	virtual ~TestCase() noexcept;

private:
	TestGroup* group;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* DEBUG_TESTCASE_H_ */
