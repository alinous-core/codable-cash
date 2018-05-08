/*
 * TestExecutor.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestExecutor.h"

#include "base/UnicodeString.h"

namespace alinous {

TestExecutor testExecInst;

TestExecutor::TestExecutor() {
}

TestExecutor::~TestExecutor() {
	auto it = this->groups.keySet()->iterator();


}

void TestExecutor::addGroup(UnicodeString* name, TestGroup* group) noexcept {
}

} /* namespace alinous */
