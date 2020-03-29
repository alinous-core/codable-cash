/*
 * test_allocation_arg.cpp
 *
 *  Created on: 2020/03/28
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
}

