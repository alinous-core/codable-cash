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

using namespace alinous;


TEST_GROUP(TestAllocationStmtGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestAllocationStmtGroup, objectAllocation){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/new01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}
