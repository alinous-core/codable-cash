/*
 * test_dom_variable.cpp
 *
 *  Created on: 2020/06/26
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtClassObject.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"

#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"

#include "engine/sc_analyze/ValidationError.h"
using namespace alinous;

TEST_GROUP(TestDomVariableGroup) {
	TEST_SETUP(){
	}

	TEST_TEARDOWN(){
	}
};

TEST(TestDomVariableGroup, testLocalDec01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestDomVariableGroup, testLocalDec02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case02/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestDomVariableGroup, testLocalDec03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case03/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestDomVariableGroup, testLocalDec04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case04/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString strCount(L"result");
	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&strCount);

	int num = count->getIntValue();
	CHECK(num == 100);
}

TEST(TestDomVariableGroup, testLocalDec05_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case05_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exname = ex->getClassName();

	CHECK(exname->equals(&NullPointerExceptionClassDeclare::NAME));
}

TEST(TestDomVariableGroup, testLocalDec06_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case06_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exname = ex->getClassName();

	CHECK(exname->equals(&TypeCastExceptionClassDeclare::NAME));
}

TEST(TestDomVariableGroup, testLocalDec07_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case07_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)

	bool bl = util.vm->hasAnalyzeError(ValidationError::CODE_TYPE_INCOMPATIBLE);
	CHECK(bl)
}

TEST(TestDomVariableGroup, testLocalDec08_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local/case08_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)

	bool bl = util.vm->hasAnalyzeError(ValidationError::CODE_TYPE_INCOMPATIBLE);
	CHECK(bl)
}
