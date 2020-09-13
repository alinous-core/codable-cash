/*
 * test_choice_methods.cpp
 *
 *  Created on: 2020/09/13
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "base/StackRelease.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "sc_analyze/ValidationError.h"
using namespace alinous;

TEST_GROUP(TestSelectMethodGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestSelectMethodGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/select/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.hasAnalyzeError(ValidationError::CODE_WRONG_FUNC_CALL_AMBIGOUS));
}

