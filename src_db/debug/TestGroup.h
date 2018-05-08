/*
 * TestGroup.h
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#ifndef DEBUG_TESTGROUP_H_
#define DEBUG_TESTGROUP_H_


namespace alinous {

class UnicodeString;
class TestExecutor;
class TestCase;
template <typename K, typename V> class HashMap;

class TestGroup {
public:
	friend class TestExecutor;
	TestGroup(const TestGroup& base) = delete;
	explicit TestGroup(const wchar_t* groupName, const char* file, int line) noexcept;
	virtual ~TestGroup() noexcept;

	void addTestCase(UnicodeString* name, TestCase* testCase) noexcept;
	virtual void execute();

private:
	UnicodeString* groupName;
	HashMap<UnicodeString, TestCase>* tests;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUP_H_ */
