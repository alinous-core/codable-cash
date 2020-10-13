/*
 * test_relational_exp.cpp
 *
 *  Created on: 2020/03/14
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


TEST_GROUP(TestRelationalExpGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

static bool getResult(ExtClassObject* obj, const wchar_t* str){
	UnicodeString strResult(str);
	ExtPrimitiveObject* oresult = obj->getExtPrimitiveObject(&strResult);
	return oresult->getBoolValue();
}

TEST(TestRelationalExpGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/relational/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	bool bl = getResult(obj, L"result");
	CHECK(bl == false);

	bl = getResult(obj, L"result2");
	CHECK(bl== false);

	bl = getResult(obj, L"result3");
	CHECK(bl== true);
}

TEST(TestRelationalExpGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/relational/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	bool bl = getResult(obj, L"result");
	CHECK(bl == false);

	bl = getResult(obj, L"result2");
	CHECK(bl== true);

	bl = getResult(obj, L"result3");
	CHECK(bl== true);
}

TEST(TestRelationalExpGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/relational/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	bool bl = getResult(obj, L"result");
	CHECK(bl == true);

	bl = getResult(obj, L"result2");
	CHECK(bl== false);

	bl = getResult(obj, L"result3");
	CHECK(bl== false);
}

TEST(TestRelationalExpGroup, case04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/relational/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	bool bl = getResult(obj, L"result");
	CHECK(bl == true);

	bl = getResult(obj, L"result2");
	CHECK(bl== true);

	bl = getResult(obj, L"result3");
	CHECK(bl== false);
}

TEST(TestRelationalExpGroup, case05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_logical/resources/relational/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

