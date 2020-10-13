/*
 * test_super_constructor.cpp
 *
 *  Created on: 2020/05/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"

#include "instance/instance_exception_class/ExceptionClassDeclare.h"

#include "engine/sc_analyze/ValidationError.h"
using namespace alinous;

TEST_GROUP(TestSuperConstructorGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestSuperConstructorGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param == 10);
}

TEST(TestSuperConstructorGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int param = VmTestUtils::getIntMemberValue(obj, L"count");

	CHECK(param == 10);
}

TEST(TestSuperConstructorGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	const UnicodeString* exname = exobj->getClassName();

	CHECK(exname->equals(ExceptionClassDeclare::NAME));
}

TEST(TestSuperConstructorGroup, case04_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case04_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_CONSTRUCTOR_MUST_BE_FIRST_STMT));
}

TEST(TestSuperConstructorGroup, case05_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/superconst/case05_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_CALL_NOSTATIC));
	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_FUNC_CALL_CANT_USE_SUPER_CONSTRUCTOR));
	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_FUNC_CALL_NAME));

}
