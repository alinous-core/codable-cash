/*
 * TestGroup.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestGroup.h"

#include "base/UnicodeString.h"

namespace alinous {

TestGroup::TestGroup(const wchar_t* groupName, const char* file, int line) noexcept {
	this->groupName = new UnicodeString(groupName);
}

TestGroup::~TestGroup() noexcept {
	delete this->groupName;
}

} /* namespace alinous */
