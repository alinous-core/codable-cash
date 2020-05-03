/*
 * test_static_invoke.cpp
 *
 *  Created on: 2020/05/02
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

TEST_GROUP(TestStaticInvokeGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStaticInvokeGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/static/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param == 1);
}

TEST(TestStaticInvokeGroup, case02_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/static/case02_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.hasAnalyzeError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_CALL_NOSTATIC));
}

