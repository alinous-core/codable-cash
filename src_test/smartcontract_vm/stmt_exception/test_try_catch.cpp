/*
 * test_try_catch.cpp
 *
 *  Created on: 2020/04/13
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"

#include "../VmTestUtils.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"
#include "ext_binary/ExtExceptionObject.h"

#include "base/UnicodeString.h"

#include "engine/sc/CodeElement.h"

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"

#include "instance/instance_exception_class/ExceptionClassDeclare.h"

#include "vm/vm_ctrl/BreakControl.h"

#include "lang/sc_declare/ClassDeclareBlock.h"

using namespace alinous;


TEST_GROUP(TestTryCatchGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestTryCatchGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case01/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case04){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)
	const UnicodeString* exname = exception->getClassName();
	CHECK(exname->equals(NullPointerExceptionClassDeclare::NAME));

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case05){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)
	const UnicodeString* exname = exception->getClassName();
	CHECK(exname->equals(ExceptionClassDeclare::NAME));

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case06){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case06/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)
	const UnicodeString* exname = exception->getClassName();
	CHECK(exname->equals(ExceptionClassDeclare::NAME));

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, case07){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/stmt_exception/resources/try/case07/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtClassObject* obj = util.getMainExtObject(); __STP(obj);
	int iresult = VmTestUtils::getIntMemberValue(obj, L"result");

	CHECK(iresult == 10)

	ExtExceptionObject* exception = VmTestUtils::getExtExceptionObject(obj, L"e");
	const CodeElement* codeElement = exception->getCodeElement();

	CHECK(codeElement->getKind() == CodeElement::STMT_THROW)

	ExtExceptionObject* exobj = util.vm->getUncaughtException(); __STP(exobj);
	CHECK(exobj == nullptr)
}

TEST(TestTryCatchGroup, test){
	BreakControl ctrl;

	CHECK(ctrl.getException() == nullptr);
}

TEST(TestTryCatchGroup, test02){
	ClassDeclareBlock block;

	CHECK(!block.hasCtrlStatement())
}

