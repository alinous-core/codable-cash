/*
 * test_dom_array_member.cpp
 *
 *  Created on: 2020/07/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

#include "sc_analyze/ValidationError.h"


using namespace alinous;

TEST_GROUP(TestDomArrayMemberGroup) {
	TEST_SETUP(){
	}

	TEST_TEARDOWN(){
	}
};


TEST(TestDomArrayMemberGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}
