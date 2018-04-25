/*
 * TestSetup.h
 *
 *  Created on: 2018/04/19
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTSETUP_H_
#define TEST_UTILS_TESTSETUP_H_

#include "base/UnicodeString.h"
#include "base_io/File.h"

extern const char* prog;


namespace alinous {

class File;

class TestSetup {
public:
	TestSetup();
	virtual ~TestSetup();

	void setup();
	void teardown();

	File testCaseDir();

	static void clearStatics();

	static UnicodeString TEST_SEG;
private:
	File* baseDir;
};

} /* namespace alinous */

#endif /* TEST_UTILS_TESTSETUP_H_ */
