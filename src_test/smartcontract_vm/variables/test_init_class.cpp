/*
 * test_init_class.cpp
 *
 *  Created on: 2020/02/21
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance_ref/VmRootReference.h"

#include "../VmTestUtils.h"

using namespace alinous;


TEST_GROUP(TestInitClass) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestInitClass, initClass){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/initclass/init01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}
