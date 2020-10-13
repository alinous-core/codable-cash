/*
 * test_dom_array.cpp
 *
 *  Created on: 2020/07/08
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"


#include "engine/sc_analyze/ValidationError.h"

#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtDomArrayObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance/instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"

using namespace alinous;

TEST_GROUP(TestDomArrayGroup) {
	TEST_SETUP(){
	}

	TEST_TEARDOWN(){
	}
};

TEST(TestDomArrayGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"result");
	ExtDomArrayObject* domArray = obj->getExtDomArrayObject(&ans);

	int maxLoop = domArray->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExtObject* element = domArray->get(i);
		ExtPrimitiveObject* pr = dynamic_cast<ExtPrimitiveObject*>(element);

		int value = pr->getIntValue();
		CHECK(value == i);
	}
}


TEST(TestDomArrayGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"result");
	ExtDomArrayObject* domArray = obj->getExtDomArrayObject(&ans);

	int maxLoop = domArray->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExtObject* element = domArray->get(i);
		ExtPrimitiveObject* pr = dynamic_cast<ExtPrimitiveObject*>(element);

		int value = pr->getIntValue();
		CHECK(value == i);
	}
}

TEST(TestDomArrayGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case03/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"count");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 5);

}

TEST(TestDomArrayGroup, case04_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case04_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case05_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case05_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case06){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case06/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"count");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 1);
}

TEST(TestDomArrayGroup, case07){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case07/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	UnicodeString ans(L"count");

	ExtPrimitiveObject* count = obj->getExtPrimitiveObject(&ans);
	int n = count->getIntValue();
	CHECK(n == 4);
}

TEST(TestDomArrayGroup, case08_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case08_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case09_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case09_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case10_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case10_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case11_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case11_err/", projectFolder, this->env);

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

TEST(TestDomArrayGroup, case12_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/variable/resources/local_array/case12_err/", projectFolder, this->env);

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


