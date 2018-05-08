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
	TestExecutor();
	virtual ~TestExecutor();

	void addGroup(UnicodeString* name, TestGroup* group) noexcept;
private:
	HashMap<UnicodeString, TestGroup> groups;
};

extern TestExecutor testExecInst;


} /* namespace alinous */

#endif /* DEBUG_TESTEXECUTOR_H_ */
