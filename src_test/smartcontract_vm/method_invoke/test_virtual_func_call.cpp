/*
 * test_virtual_func_call.cpp
 *
 *  Created on: 2020/04/03
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "base/StackRelease.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

using namespace alinous;

TEST_GROUP(TestVFunctionCallGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVFunctionCallGroup, test01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/vfunc/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param = 20);
}

TEST(TestVFunctionCallGroup, test02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/vfunc/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param = 20);
}


