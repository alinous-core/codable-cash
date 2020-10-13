/*
 * test_pre_inc.cpp
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

TEST_GROUP(TestPreIncGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestPreIncGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 2);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 2);
}

TEST(TestPreIncGroup, case01_m){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case01_m/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 0);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(lastcount->getIntValue() == 0);
}

/////////////////////////////////////////////////////////////////////////////

TEST(TestPreIncGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 2);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 2);
}

TEST(TestPreIncGroup, case02_m){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case02_m/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getByteValue() == 0);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(lastcount->getByteValue() == 0);
}

/////////////////////////////////////////////////////////////////////////////

TEST(TestPreIncGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getShortValue() == 2);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getShortValue() == 2);
}

TEST(TestPreIncGroup, case03_m){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case03_m/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getShortValue() == 0);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(lastcount->getShortValue() == 0);
}

/////////////////////////////////////////////////////////////////////////////

TEST(TestPreIncGroup, case04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getLongValue() == 2);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getLongValue() == 2);
}

TEST(TestPreIncGroup, case04_m){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case04_m/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getLongValue() == 0);

	UnicodeString strLastCount(L"lastcount");
	ExtPrimitiveObject* lastcount = obj->getExtPrimitiveObject(&strCount);

	CHECK(lastcount->getLongValue() == 0);
}

/////////////////////////////////////////////////////////////////////////////

TEST(TestPreIncGroup, case05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/exp_arithmetic/resources/preinc/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}
