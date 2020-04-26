/*
 * test_static_variables.cpp
 *
 *  Created on: 2020/04/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "sc_analyze/ValidationError.h"

#include "../VmTestUtils.h"

using namespace alinous;


TEST_GROUP(TestStaticVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStaticVariablesGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/static/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}

