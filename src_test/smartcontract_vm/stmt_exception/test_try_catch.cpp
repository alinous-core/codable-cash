/*
 * test_try_catch.cpp
 *
 *  Created on: 2020/04/13
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"


using namespace alinous;


TEST_GROUP(TestTryCatchGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTryCatchGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

/*
	result = util.createInstance();
	CHECK(result)
	*/
}
