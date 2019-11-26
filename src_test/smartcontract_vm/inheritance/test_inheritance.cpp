/*
 * test_inheritance.cpp
 *
 *  Created on: 2019/11/23
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"

using namespace alinous;

TEST_GROUP(TestInheritanceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestInheritanceGroup, inheritance){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");
	// FIXME test

}

