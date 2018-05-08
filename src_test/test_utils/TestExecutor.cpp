/*
 * TestExecutor.cpp
 *
 *  Created on: 2018/05/06
 *      Author: iizuka
 */

#include "test_utils/TestExecutor.h"
#include "test_utils/TestGroup.h"
#include "test_utils/TestParams.h"
#include "base/UnicodeString.h"

#include "osenv/funcs.h"

namespace alinous {

TestExecutor::TestExecutor() {
	this->groups = new HashMap<UnicodeString, TestGroup>();
	this->initialized = false;
}

TestExecutor* TestExecutor::get() noexcept {
	static TestExecutor testExecInst;

	return &testExecInst;
}

TestExecutor::~TestExecutor() {
	delete this->groups;
}

void TestExecutor::addGroup(UnicodeString* name, TestGroup* group) noexcept {
	this->groups->put(name, group);
}

int TestExecutor::execute(int ac, char** av) noexcept {
	if(!this->initialized){
		init(av[0]);
	}

	TestParams params;

	try{
		params.init(ac, av);
	}catch(TestParamsException* ex){
		printf("Wrong parameter...\n");
		return -1;
	}

	printf("Start Testing...\n");

	execTest();

	printf("Testing Summary\n");

	return 1;
}

void TestExecutor::execTest() noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);

		grp->execute();
	}
	delete it;
}

void TestExecutor::init(const char* prog) noexcept {
	auto* it = this->groups->keySet()->iterator();
	while(it->hasNext()){
		const UnicodeString* key = it->next();
		TestGroup* grp = this->groups->get(key);
		grp->init(prog);
	}
	delete it;
}



} /* namespace alinous */
