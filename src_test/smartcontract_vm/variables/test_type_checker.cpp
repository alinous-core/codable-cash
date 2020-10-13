/*
 * test_type_checker.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "base/StackRelease.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "vm/type_check/AnalyzedTypeChecker.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/type_check/InternalTypeChecker.h"

#include "engine/sc_analyze/ValidationError.h"

using namespace alinous;

TEST_GROUP(TestTypeCheckGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTypeCheckGroup, construct){
	AnalyzedTypeChecker checker;
}

TEST(TestTypeCheckGroup, intnl01){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}

TEST(TestTypeCheckGroup, intnl02){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right;

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnl03){
	AnalyzedType left;
	AnalyzedType right;

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::NO_CHECK == ret);
}

TEST(TestTypeCheckGroup, intnl04){
	AnalyzedType left(AnalyzedType::TYPE_BOOL);
	AnalyzedType right(AnalyzedType::TYPE_BOOL);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}

TEST(TestTypeCheckGroup, intnl05){
	AnalyzedType left(AnalyzedType::TYPE_BOOL);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnl06){
	AnalyzedType left(AnalyzedType::TYPE_STRING);
	AnalyzedType right(AnalyzedType::TYPE_STRING);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::OK == ret);
}


TEST(TestTypeCheckGroup, intnl07){
	AnalyzedType left(AnalyzedType::TYPE_STRING);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnlDim){
	AnalyzedType left(AnalyzedType::TYPE_INT);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	left.setDim(2);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnlObject){
	AnalyzedType left(AnalyzedType::TYPE_OBJECT);
	AnalyzedType right(AnalyzedType::TYPE_INT);

	int ret = InternalTypeChecker::analyzeCompatibility(&left, &right);
	CHECK(InternalTypeChecker::INCOMPATIBLE == ret);
}

TEST(TestTypeCheckGroup, intnlObjectTest01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}

TEST(TestTypeCheckGroup, intnlObjectTest02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}

TEST(TestTypeCheckGroup, intnlObjectTest03_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case03_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestTypeCheckGroup, intnlObjectTest04){ // null
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}

TEST(TestTypeCheckGroup, intnlObjectTest05_err){ // null
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)
}

TEST(TestTypeCheckGroup, intnlObjectTest06){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case06/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)
}

TEST(TestTypeCheckGroup, memberVariable_error01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case07_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_TYPE_NAME));
}

TEST(TestTypeCheckGroup, memberVariable_error02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/variables/resources/typecheck/case08_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::CODE_WRONG_TYPE_NAME));
}
