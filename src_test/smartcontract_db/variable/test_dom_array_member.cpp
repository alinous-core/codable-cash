/*
 * test_dom_array_member.cpp
 *
 *  Created on: 2020/07/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

#include "engine/sc_analyze/ValidationError.h"

#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtClassObject.h"

#include "instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
#include "instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance_exception/TypeCastExceptionClassDeclare.h"

using namespace alinous;

TEST_GROUP(TestDomArrayMemberGroup) {
	TEST_SETUP(){
	}

	TEST_TEARDOWN(){
	}
};


TEST(TestDomArrayMemberGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"result");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 1);
}

TEST(TestDomArrayMemberGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case02/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"result");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 5);
}

TEST(TestDomArrayMemberGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case03/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"result");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 3);
}

TEST(TestDomArrayMemberGroup, case04_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case04_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

	const UnicodeString* name = ex->getClassName();
	CHECK(name->equals(ArrayOutOfBoundsExceptionClassDeclare::NAME));
}

TEST(TestDomArrayMemberGroup, case05_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case05_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

	const UnicodeString* name = ex->getClassName();
	CHECK(name->equals(ArrayOutOfBoundsExceptionClassDeclare::NAME));
}

TEST(TestDomArrayMemberGroup, case06_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case06_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

	const UnicodeString* name = ex->getClassName();
	CHECK(name->equals(NullPointerExceptionClassDeclare::NAME));
}

TEST(TestDomArrayMemberGroup, case07_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case07_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

	const UnicodeString* name = ex->getClassName();
	CHECK(name->equals(TypeCastExceptionClassDeclare::NAME));
}

TEST(TestDomArrayMemberGroup, case08_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/member_array/case08_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

	const UnicodeString* name = ex->getClassName();
	CHECK(name->equals(TypeCastExceptionClassDeclare::NAME));
}

