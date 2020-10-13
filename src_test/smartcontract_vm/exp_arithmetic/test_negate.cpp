/*
 * test_negate.cpp
 *
 *  Created on: 2020/03/07
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

TEST_GROUP(TestNegateGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestNegateGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/negate/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 1);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strLastCount);

	CHECK(lastcount->getIntValue() == -1);
}

TEST(TestNegateGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/negate/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getByteValue() == 1);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strLastCount);

	CHECK(lastcount->getByteValue() == -1);
}

TEST(TestNegateGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/negate/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getShortValue() == 1);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strLastCount);

	CHECK(lastcount->getShortValue() == -1);
}

TEST(TestNegateGroup, case04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/negate/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getLongValue() == 1);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strLastCount);

	CHECK(lastcount->getLongValue() == -1);
}

TEST(TestNegateGroup, case05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/negate/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}
