/*
 * test_allocation_arg.cpp
 *
 *  Created on: 2020/03/28
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtArrayObject.h"

using namespace alinous;


TEST_GROUP(TestAllocationArgGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestAllocationArgGroup, intArg){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new_arg/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	ExtClassObject* objectA = VmTestUtils::getObjectValue(obj, L"obj");
	int param = VmTestUtils::getIntMemberValue(objectA, L"param");

	CHECK(param == 100)
}

TEST(TestAllocationArgGroup, objectArg01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new_arg/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	ExtClassObject* objectA = VmTestUtils::getObjectValue(obj, L"obj");
	ExtClassObject* objectB = VmTestUtils::getObjectValue(objectA, L"obj");

	int param = VmTestUtils::getIntMemberValue(objectB, L"param");

	CHECK(param == 100)
}

TEST(TestAllocationArgGroup, objectArg02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new_arg/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	ExtClassObject* objectA = VmTestUtils::getObjectValue(obj, L"obj");
	ExtClassObject* objectB = VmTestUtils::getObjectValue(objectA, L"objb");

	int param = VmTestUtils::getIntMemberValue(objectB, L"param");

	CHECK(param == 100)
}

TEST(TestAllocationArgGroup, objectArg03){ // null
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new_arg/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	ExtClassObject* objectA = VmTestUtils::getObjectValue(obj, L"obj");
	ExtClassObject* objectB = VmTestUtils::getObjectValue(objectA, L"objb");

	CHECK(objectB == nullptr)
}

TEST(TestAllocationArgGroup, objectArg04_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new_arg/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

