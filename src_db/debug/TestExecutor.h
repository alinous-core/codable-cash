/*
 * TestExecutor.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTEXECUTOR_H_
#define DEBUG_TESTEXECUTOR_H_

#include "base/HashMap.h"


namespace alinous {

class UnicodeString;
class TestGroup;

class TestExecutor {
public:
	TestExecutor(const TestExecutor& base) = delete;
	TestExecutor();
	virtual ~TestExecutor();

	static TestExecutor* get() noexcept;
	void addGroup(UnicodeString* name, TestGroup* group) noexcept;

	void execute(int ac, char** av) noexcept;
private:
	void init(const char* prog) noexcept;
private:
	HashMap<UnicodeString, TestGroup>* groups;
	bool initialized;
};



} /* namespace alinous */

#endif /* DEBUG_TESTEXECUTOR_H_ */
