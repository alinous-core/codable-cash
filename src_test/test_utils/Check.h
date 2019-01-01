/*
 * Check.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_CHECK_H_
#define DEBUG_CHECK_H_

#include "osenv/funcs.h"
#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
class TestCase;

typedef struct __threadKeySet {
	THREAD_ID id;
	THREAD_KEY key;
} ThreadKeySet;

class ThreadKeyRegistory {
public:
	ThreadKeyRegistory();
	~ThreadKeyRegistory();

	void registerTestCase(TestCase* testCase);
	ThreadKeySet* getKey();
private:
	ArrayList<ThreadKeySet> list;
};

class Check {
public:
	static ThreadKeyRegistory* getThreadKeyRegistory();

	Check(const Check& base) = delete;
	Check(TestCase* testCase, const char* file, int line);
	virtual ~Check();

	void checkCondition(bool condition) noexcept;
	bool isOk() const noexcept;

	int getLine() const {
		return line;
	}

protected:
	bool ok;
	UnicodeString* file;
	int line;
	TestCase* testCase;
};

Check* __mcAddcheck(alinous::Check* chk);

} /* namespace alinous */

#endif /* DEBUG_CHECK_H_ */
