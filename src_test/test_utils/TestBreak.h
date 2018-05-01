/*
 * TestBreak.h
 *
 *  Created on: 2018/05/01
 *      Author: iizuka
 */

#ifndef TEST_UTILS_TESTBREAK_H_
#define TEST_UTILS_TESTBREAK_H_

#include "base_thread/SynchronizedLock.h"

namespace alinous {

class TestBreak {
public:
	TestBreak();
	virtual ~TestBreak();

	void resume(int num);

	void breakpoint(int num);
	int current();
private:
	SynchronizedLock lock;
	int location;


};

} /* namespace alinous */

#endif /* TEST_UTILS_TESTBREAK_H_ */
