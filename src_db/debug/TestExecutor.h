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

	static TestExecutor* get() noexcept {
		static TestExecutor testExecInst;

		return &testExecInst;
	}
	void addGroup(UnicodeString* name, TestGroup* group) noexcept;

	void execute() noexcept;
private:
	HashMap<UnicodeString, TestGroup>* groups;
};



} /* namespace alinous */

#endif /* DEBUG_TESTEXECUTOR_H_ */
