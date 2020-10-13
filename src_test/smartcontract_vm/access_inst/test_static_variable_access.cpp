/*
 * test_static_variable_access.cpp
 *
 *  Created on: 2020/04/29
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "vm/variable_access/ClassTypeAccess.h"

using namespace alinous;


TEST_GROUP(TestStaticVariableAccessGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStaticVariableAccessGroup, getElement){
	AnalyzedType at;
	ClassTypeAccess ac(&at);
	CHECK(ac.getCodeElement() == nullptr)
}

TEST(TestStaticVariableAccessGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/staticv/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"count");
	CHECK(iresult == 1);
}

TEST(TestStaticVariableAccessGroup, case02_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/staticv/case02_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestStaticVariableAccessGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/staticv/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"count");
	CHECK(iresult == 1);
}

TEST(TestStaticVariableAccessGroup, case04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/staticv/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"count");
	CHECK(iresult == 1);
}

TEST(TestStaticVariableAccessGroup, case05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/staticv/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"count");
	CHECK(iresult == 1);
}
