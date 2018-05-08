/*
 * TestCase.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTCASE_H_
#define DEBUG_TESTCASE_H_

#include "base/ArrayList.h"

namespace alinous {

class TestGroup;
class TestGroupActions;
class UnicodeString;
class Check;

class TestCase {
public:
	TestCase(const TestCase& base) = delete;
	TestCase(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) noexcept;
	virtual ~TestCase() noexcept;

	virtual void testBody() = 0;
	void doTest();

	Check* addCheck(Check* check) noexcept;
private:
	TestGroup* group;
	TestGroupActions* setup;

	UnicodeString* file;
	int line;
	UnicodeString* name;

	ArrayList<Check>* checks;

};

} /* namespace alinous */

#endif /* DEBUG_TESTCASE_H_ */
