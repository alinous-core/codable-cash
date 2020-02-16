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

}
