/*
 * test_inheritance.cpp
 *
 *  Created on: 2019/11/23
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "engine/sc_analyze/ValidationError.h"

using namespace alinous;

TEST_GROUP(TestInheritanceGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestInheritanceGroup, inheritance){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

}

TEST(TestInheritanceGroup, inheritance_err01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case02_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_CLASS_NAME))
}

TEST(TestInheritanceGroup, inheritance_err02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case03_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_IMPORT_FORMAT))
}

TEST(TestInheritanceGroup, inheritance_err03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/inheritance/resources/case04_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_CLASS_MEMBER_ALREADY_EXISTS))
}
