/*
 * Check.h
 *
 *  Created on: 2018/05/08
 *      Author: iizuka
 */

#ifndef DEBUG_CHECK_H_
#define DEBUG_CHECK_H_

namespace alinous {
class UnicodeString;
class TestCase;

class Check {
public:
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

} /* namespace alinous */

#endif /* DEBUG_CHECK_H_ */
