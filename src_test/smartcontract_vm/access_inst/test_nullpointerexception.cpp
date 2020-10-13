/*
 * test_nullpointerexception.cpp
 *
 *  Created on: 2020/04/28
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

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
using namespace alinous;


TEST_GROUP(TestNullPointerExceptionGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestNullPointerExceptionGroup, case01) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/nullptr/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	const UnicodeString* exname = exobj->getClassName();

	CHECK(exname->equals(NullPointerExceptionClassDeclare::NAME));
}

TEST(TestNullPointerExceptionGroup, case02) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/access_inst/resources/nullptr/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	const UnicodeString* exname = exobj->getClassName();

	CHECK(exname->equals(NullPointerExceptionClassDeclare::NAME));
}
