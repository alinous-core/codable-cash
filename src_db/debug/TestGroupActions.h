/*
 * TestGroupSetup.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_TESTGROUPACTIONS_H_
#define DEBUG_TESTGROUPACTIONS_H_

namespace alinous {

class UnicodeString;
class TestEnv;

class TestGroupActions {
public:
	TestGroupActions(const TestGroupActions& base) = delete;
	TestGroupActions();
	virtual ~TestGroupActions();
	virtual void setup();
	virtual void teardown();

	void setNames(UnicodeString* testGroupName, UnicodeString* testCaseName) noexcept;
	void setTestEnv(TestEnv* env) noexcept;
protected:
	UnicodeString* testCaseName;
	UnicodeString* testGroupName;

	TestEnv* env;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUPACTIONS_H_ */
