/*
 * test_main_vm.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

using namespace alinous;


TEST_GROUP(TestVMGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};


TEST(TestVMGroup, construct){
	VirtualMachine* vm = new VirtualMachine(1024);
	delete vm;
}

TEST(TestVMGroup, loadAndExec){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/hello.alns"))

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	VirtualMachine* vm = new VirtualMachine(1024);
	vm->loadSmartContract(sc);

	delete vm;
}


TEST(TestVMGroup, loadAndExec2){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract/resources/parser/hello.alns"));


	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	VirtualMachine* vm = new VirtualMachine(1024);
	vm->loadSmartContract(sc);

	vm->analyze();

	delete vm;
}

TEST(TestVMGroup, loadAndInitInstance){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/resources/main.alns"));

	SmartContract* sc = new SmartContract();
	FileInputStream stream(sourceFile);

	int length = sourceFile->length();
	sc->addCompilationUnit(&stream, length);

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);


	VirtualMachine* vm = new VirtualMachine(1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
}


