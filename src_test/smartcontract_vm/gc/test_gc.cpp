/*
 * test_gc.cpp
 *
 *  Created on: 2020/05/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"

#include "instance/instance_gc/GcManager.h"
using namespace alinous;

TEST_GROUP(TestGcGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestGcGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/gc/resources/gc/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	util.vm->releaseMainInstance();
	GcManager* gc = util.vm->getGc();
	gc->garbageCollect();

	util.vm->destroy();
}

TEST(TestGcGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/gc/resources/gc/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	GcManager* gc = util.vm->getGc();
	gc->garbageCollect();

	util.vm->destroy();
}
