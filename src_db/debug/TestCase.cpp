/*
 * TestCase.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestCase.h"
#include "debug/TestGroup.h"
#include "base/UnicodeString.h"

namespace alinous {

TestCase::TestCase(TestGroup* group, UnicodeString* name) noexcept {
	this->group = group;
	this->name = new UnicodeString(name);

}

TestCase::~TestCase() noexcept {
	delete this->group;
	delete this->name;
}

} /* namespace alinous */
