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

class TestGroupActions {
public:
	TestGroupActions(const TestGroupActions& base) = delete;
	TestGroupActions();
	virtual ~TestGroupActions();
	virtual void setup();
	virtual void teardown();

	void setNames(UnicodeString* testGroupName, UnicodeString* testCaseName) noexcept;
protected:
	UnicodeString* testCaseName;
	UnicodeString* testGroupName;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUPACTIONS_H_ */
