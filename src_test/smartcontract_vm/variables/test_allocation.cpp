/*
 * test_allocation.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtArrayObject.h"

using namespace alinous;


TEST_GROUP(TestAllocationStmtGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestAllocationStmtGroup, objectAllocation){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	// obj
	UnicodeString objA(L"obj");
	ExtClassObject* objobj = obj->getExtClassObject(&objA);

	CHECK(objobj != nullptr)

}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new02/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* extObj = util.getMainExtObject(); __STP(extObj);
	UnicodeString strar(L"ar");
	ExtArrayObject* arObj = extObj->getExtArrayObject(&strar);

	CHECK(arObj != nullptr)

	int length = arObj->getLength();
	CHECK(length == 3)

}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new03/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* extObj = util.getMainExtObject(); __STP(extObj);
	UnicodeString strar(L"ar");
	ExtArrayObject* arObj = extObj->getExtArrayObject(&strar);

	CHECK(arObj != nullptr)

	int length = arObj->getLength();
	CHECK(length == 3)

	arObj = (ExtArrayObject*)arObj->get(2);
	length = arObj->getLength();
	CHECK(length == 4)

	arObj = (ExtArrayObject*)arObj->get(3);
	length = arObj->getLength();
	CHECK(length == 5)
}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new04/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new05/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation06){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new06_err/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)
}

TEST(TestAllocationStmtGroup, primitiveArrayAllocation07){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new/new07_err/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)
}
