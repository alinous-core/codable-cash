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
	explicit TestGroup(UnicodeString* groupName) noexcept;
	virtual ~TestGroup() noexcept;

private:
	UnicodeString* groupName;
};

} /* namespace alinous */

#endif /* DEBUG_TESTGROUP_H_ */
