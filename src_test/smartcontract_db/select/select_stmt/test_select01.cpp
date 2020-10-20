/*
 * test_select01.cpp
 *
 *  Created on: 2020/06/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

using namespace alinous;
//using namespace codablecash;

TEST_GROUP(TestSelect01Group) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestSelect01Group, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/select/select_stmt/resources/select01/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

