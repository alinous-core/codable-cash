/*
 * test_function_call.cpp
 *
 *  Created on: 2019/12/09
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

TEST_GROUP(TestFunctionCallGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestFunctionCallGroup, callMainMethod){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/func01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
	if(!result){
		return;
	}

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString count(L"count");
	ExtPrimitiveObject* countObj = obj->getExtPrimitiveObject(&count);

	CHECK(countObj->getIntValue() == 2)
}

TEST(TestFunctionCallGroup, invokeMember01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/invoke01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString count(L"count");
	ExtPrimitiveObject* countObj = obj->getExtPrimitiveObject(&count);

	CHECK(countObj->getIntValue() == 2)
}

TEST(TestFunctionCallGroup, invokeMember02_error){
	// invoke02_error
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/invoke02_error/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestFunctionCallGroup, invokeMember03_error){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/invoke03_error/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestFunctionCallGroup, constructor01_error){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/constructor01_error/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestFunctionCallGroup, compile_error){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/methods/compile_error/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}


