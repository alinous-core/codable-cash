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

	bool v;
	ArrayList<UnicodeString, UnicodeString::ValueCompare> execGroups;
};

} /* namespace alinous */

class TestParamsException{
public:
};

#endif /* TEST_UTILS_TESTPARAMS_H_ */
