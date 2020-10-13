/*
 * test_local_variavle.cpp
 *
 *  Created on: 2019/12/14
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance/instance_ref/VmRootReference.h"
#include "instance/VmClassInstance.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze_functions/VTableRegistory.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "engine/sc_analyze/ValidationError.h"
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
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

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
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

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
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

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
		int ival = val->getIntValue();
		CHECK(ival == 100);
	}

	vm->destroy();
}

TEST(TestLocalVariablesGroup, error01){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/localvariables/stack03_err/intval.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();

	AnalyzeContext* actx = vm->getSmartContract()->getAnalyzeContext();
	const ArrayList<ValidationError>* list = actx->getErrors();
	int size = list->size();

	CHECK(size >= 1);
	if(size > 0){
		bool hascode = false;
		for(int i = 0; i != size; ++i){
			ValidationError* error = list->get(i);
			int code = error->getErrorCode();
			if(code == ValidationError::CODE_CLASS_MEMBER_AND_STACK_VARIABLE_DO_NOT_EXISTS){
				hascode = true;
			}
		}

		CHECK(hascode);
	}
}

TEST(TestLocalVariablesGroup, error02){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/localvariables/stack04_err/intval.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length, projectFolder, sourceFile);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();

	AnalyzeContext* actx = vm->getSmartContract()->getAnalyzeContext();
	const ArrayList<ValidationError>* list = actx->getErrors();
	int size = list->size();

	CHECK(size >= 1);
	if(size > 0){
		bool hascode = false;
		for(int i = 0; i != size; ++i){
			ValidationError* error = list->get(i);
			int code = error->getErrorCode();
			if(code == ValidationError::CODE_TYPE_DOES_NOT_EXISTS){
				hascode = true;
			}
		}

		CHECK(hascode);
	}
}
