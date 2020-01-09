/*
 * test_super_variables.cpp
 *
 *  Created on: 2019/12/19
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"

#include "ext_binary/ExtClassObject.h"

using namespace alinous;

TEST_GROUP(TestSuperVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestSuperVariablesGroup, inheritance){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/sv01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}



TEST(TestSuperVariablesGroup, inheritanceCreate){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/sv01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject();

	delete obj;
}

