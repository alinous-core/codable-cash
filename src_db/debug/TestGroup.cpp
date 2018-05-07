/*
 * TestGroup.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestGroup.h"

#include "base/UnicodeString.h"

namespace alinous {

TestGroup::TestGroup(UnicodeString* groupName) noexcept {
	this->groupName = new UnicodeString(groupName);
}

TestGroup::~TestGroup() noexcept {
	delete this->groupName;
}

} /* namespace alinous */
