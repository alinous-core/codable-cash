/*
 * test_dom_member_variable.cpp
 *
 *  Created on: 2020/07/05
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtClassObject.h"

#include "instance_exception/NullPointerExceptionClassDeclare.h"

#include "instance_exception/TypeCastExceptionClassDeclare.h"

#include "sc_analyze/ValidationError.h"
using namespace alinous;

TEST_GROUP(TestDomMemberVariableGroup) {
	TEST_SETUP(){
	}

	TEST_TEARDOWN(){
	}
};

TEST(TestDomMemberVariableGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}
