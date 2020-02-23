/*
 * test_local_variavle.cpp
 *
 *  Created on: 2019/12/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance_ref/VmRootReference.h"
#include "instance/VmClassInstance.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze_functions/VTableRegistory.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"

#include "ext_binary/ExtPrimitiveObject.h"
using namespace alinous;


TEST_GROUP(TestLocalVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestLocalVariablesGroup, intVariable){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/localvariables/intval/intval.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	vm->createScInstance();
	vm->destroy();
}

TEST(TestLocalVariablesGroup, intaccess){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/localvariables/stack01/intval.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	VmClassInstance* mainInst = vm->createScInstance();

	{
		AnalyzeContext* actx = sc->getAnalyzeContext();
		VTableRegistory* reg = actx->getVtableRegistory();

		UnicodeString name(L"name");
		AbstractExtObject* extObj = mainInst->toClassExtObject(&name, reg); __STP(extObj);

		ExtClassObject* classObj = dynamic_cast<ExtClassObject*>(extObj);

		UnicodeString strVal(L"val");
		ExtPrimitiveObject* val = classObj->getExtPrimitiveObject(&strVal);
		CHECK(val->getIntValue() == 10);
	}

	vm->destroy();
}

TEST(TestLocalVariablesGroup, intaccessWithMember){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/localvariables/stack02/intval.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	VmClassInstance* mainInst = vm->createScInstance();

	{
		AnalyzeContext* actx = sc->getAnalyzeContext();
		VTableRegistory* reg = actx->getVtableRegistory();

		UnicodeString name(L"name");
		AbstractExtObject* extObj = mainInst->toClassExtObject(&name, reg); __STP(extObj);

		ExtClassObject* classObj = dynamic_cast<ExtClassObject*>(extObj);

		UnicodeString strVal(L"val2");
		ExtPrimitiveObject* val = classObj->getExtPrimitiveObject(&strVal);
		CHECK(val->getIntValue() == 100);
	}

	vm->destroy();
}

