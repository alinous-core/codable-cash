/*
 * test_super_constructor.cpp
 *
 *  Created on: 2020/05/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"

using namespace alinous;

TEST_GROUP(TestSuperConstructorGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestSuperConstructorGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param == 10);
}
