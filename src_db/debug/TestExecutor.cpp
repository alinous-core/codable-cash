/*
 * TestExecutor.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "debug/TestExecutor.h"
#include "debug/TestGroup.h"
#include "base/UnicodeString.h"

namespace alinous {

TestExecutor::TestExecutor() {
	this->groups = new HashMap<UnicodeString, TestGroup>();
}

TestExecutor::~TestExecutor() {
	delete this->groups;
}

void TestExecutor::addGroup(UnicodeString* name, TestGroup* group) noexcept {
	this->groups->put(name, group);
}

void TestExecutor::execute() noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);

		grp->execute();
	}

	delete it;
}

} /* namespace alinous */
