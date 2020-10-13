/*
 * test_equality_exp.cpp
 *
 *  Created on: 2020/03/08
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


using namespace alinous;


TEST_GROUP(TestEqualityGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestEqualityGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/eq/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strResult(L"result");
	ExtPrimitiveObject* oresult = obj->getExtPrimitiveObject(&strResult);

	bool bl = oresult->getBoolValue();

	CHECK(oresult->getBoolValue() == false);
}

TEST(TestEqualityGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/eq/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strResult(L"result");
	ExtPrimitiveObject* oresult = obj->getExtPrimitiveObject(&strResult);

	bool bl = oresult->getBoolValue();

	CHECK(oresult->getBoolValue() == true);
}
