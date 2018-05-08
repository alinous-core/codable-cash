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

class TestGroup {
public:
	explicit TestGroup(const wchar_t* groupName, const char* file, int line) noexcept;
	virtual ~TestGroup() noexcept;

private:
	UnicodeString* groupName;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUP_H_ */
