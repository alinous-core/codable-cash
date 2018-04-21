/*
 * TestCountRunner.h
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#ifndef DB_BASE_THREAD_TESTCOUNTRUNNER_H_
#define DB_BASE_THREAD_TESTCOUNTRUNNER_H_

#include "base_thread/AbstractThreadRunner.h"

namespace alinous {

class UnicodeString;

class TestCountRunner : public AbstractThreadRunner {
public:
	TestCountRunner(const UnicodeString* name);
	TestCountRunner();
	virtual ~TestCountRunner();

	virtual void process() noexcept;
};

} /* namespace alinous */

#endif /* DB_BASE_THREAD_TESTCOUNTRUNNER_H_ */
