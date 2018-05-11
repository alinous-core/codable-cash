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
class TestParams;
class TestSummary;
template <typename K, typename V> class HashMap;
class Writer;

class TestGroup {
public:
	friend class TestExecutor;
	TestGroup(const TestGroup& base) = delete;
	explicit TestGroup(const wchar_t* groupName, const char* file, int line) noexcept;
	virtual ~TestGroup() noexcept;

	void init(const char* prog) noexcept;

	void addTestCase(UnicodeString* name, TestCase* testCase) noexcept;
	virtual void execute(TestParams* params);
	void summaryTest(TestSummary* summary) noexcept;
	void exportJUnitXML(Writer* writer) const;

	UnicodeString* getName() const noexcept;

private:
	UnicodeString* groupName;
	HashMap<UnicodeString, TestCase>* tests;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUP_H_ */
