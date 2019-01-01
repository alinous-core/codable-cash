/*
 * TestCase.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTCASE_H_
#define DEBUG_TESTCASE_H_

#include "base/ArrayList.h"
#include <stdint.h>

#include "osenv/funcs.h"

namespace alinous {

class TestGroup;
class TestGroupActions;
class UnicodeString;
class Check;
class TestEnv;
class TestParams;
class Writer;

class TestCase {
public:
	static THREAD_KEY TEST_CASE_KEY;

	TestCase(const TestCase& base) = delete;
	TestCase(TestGroup* group, const wchar_t* name, TestGroupActions* setup, const char* file, int line) noexcept;
	virtual ~TestCase() noexcept;

	virtual void testBody() = 0;
	void doTest(TestParams* params);

	Check* addCheck(Check* check) noexcept;

	const TestGroup* getGroup() const noexcept;
	TestEnv* getEnv() noexcept;
	const UnicodeString* getName() const noexcept;

	const UnicodeString* getFile() const noexcept;
	const int getLine() const noexcept;

	bool isDone() const noexcept;
	void setDone() noexcept;
	bool isFailed() const noexcept;
	void setFailed() noexcept;

	ArrayList<Check>* getChecks() const noexcept;
	void exportJUnitXML(Writer* writer) const;

private:
	TestGroup* group;
	TestGroupActions* setup;

	UnicodeString* file;
	int line;
	UnicodeString* name;

	ArrayList<Check>* checks;
	bool done;
	bool failed;
	uint64_t microsec;

protected:
	TestEnv* env;
};

} /* namespace alinous */

#endif /* DEBUG_TESTCASE_H_ */
