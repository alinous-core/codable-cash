/*
 * TestEnv.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_TESTENV_H_
#define DEBUG_TESTENV_H_


extern const char* prog;

namespace alinous {

class TestGroupActions;
class TestCase;
class File;
class UnicodeString;

class TestEnv {
public:
	TestEnv(TestCase* testCase);
	virtual ~TestEnv();

	void init(const char* prog) noexcept;

	void setup();
	void teardown();

	File testCaseDir();

	static const UnicodeString* TEST_SEG();

	TestCase* getTestCase() const {
		return testCase;
	}

	const File* getProjectRoot() const {
		return projectRoot;
	}

private:
	File* baseDir;
	File* projectRoot;

protected:
	TestCase* testCase;
};

} /* namespace alinous */

#endif /* DEBUG_TESTENV_H_ */
