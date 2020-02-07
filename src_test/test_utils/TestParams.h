/*
 * TestParams.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTPARAMS_H_
#define TEST_UTILS_TESTPARAMS_H_

#include "base/ArrayList.h"
#include "base/UnicodeString.h"

namespace alinous {

class TestParams {
public:
	TestParams() noexcept;
	virtual ~TestParams() noexcept;

	void init(int ac, char** av);
	static char* nextParam(int* i, char** av, int length);

	bool skipGroup(const UnicodeString* grp) const noexcept;
	bool skipTest(const UnicodeString* t) const noexcept;
	bool isV() const noexcept {
		return this->v;
	}
private:
	bool v;
	ArrayList<UnicodeString, UnicodeString::ValueCompare> execGroups;
	UnicodeString* testName;
};

} /* namespace alinous */

class TestParamsException{
public:
};

#endif /* TEST_UTILS_TESTPARAMS_H_ */
