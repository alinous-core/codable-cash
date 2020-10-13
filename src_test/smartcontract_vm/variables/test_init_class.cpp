/*
 * test_init_class.cpp
 *
 *  Created on: 2020/02/21
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance/instance_ref/VmRootReference.h"

#include "../VmTestUtils.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

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

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	CHECK(count->getIntValue() == 10);
}

TEST(TestInitClass, initClassObject){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/initclass/init02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strObj(L"obj");
	ExtClassObject* innerObj = obj->getExtClassObject(&strObj);

	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = innerObj->getExtPrimitiveObject(&strCount);

	int val = count->getIntValue();
	CHECK(val == 5);
}

TEST(TestInitClass, initExtClassObject){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/initclass/init02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);

	ExtClassObject* obj2 = dynamic_cast<ExtClassObject*>(obj->copy()); __STP(obj2);

	UnicodeString strObj(L"obj");
	ExtClassObject* innerObj = obj2->getExtClassObject(&strObj);

	UnicodeString strCount(L"count");
	ExtPrimitiveObject* count = innerObj->getExtPrimitiveObject(&strCount);

	int val = count->getIntValue();
	CHECK(val == 5);
}
