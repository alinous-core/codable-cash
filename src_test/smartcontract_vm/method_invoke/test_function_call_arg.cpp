/*
 * test_function_call_arg.cpp
 *
 *  Created on: 2020/04/01
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

using namespace alinous;

TEST_GROUP(TestFunctionCallArgGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestFunctionCallArgGroup, arg01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/arg/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param == 100);
}
