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

class Check {
public:
	Check(const Check& base) = delete;
	Check(const char* file, int line);
	virtual ~Check();

	void checkCondition(bool condition) noexcept;

protected:
	bool ok;
	UnicodeString* file;
	int line;
};

} /* namespace alinous */

#endif /* DEBUG_CHECK_H_ */
