/*
 * test_variables.cpp
 *
 *  Created on: 2019/11/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance_ref/ObjectReference.h"

using namespace alinous;


TEST_GROUP(TestVmVariableGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmVariableGroup, abstracts){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/objref/main.alns"));
	_ST(File, sourceFile2, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/objref/obj.alns"));

	SmartContract* sc = new SmartContract();
	{
		FileInputStream stream(sourceFile);
		int length = sourceFile->length();
		sc->addCompilationUnit(&stream, length);
	}
	{
		FileInputStream stream(sourceFile2);
		int length = sourceFile2->length();
		sc->addCompilationUnit(&stream, length);
	}

	UnicodeString mainPackage(L"test.fw");
	UnicodeString mainClass(L"SmartContract");
	UnicodeString mainMethod(L"main");
	sc->setMainMethod(&mainPackage, &mainClass, &mainMethod);

	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	vm->loadSmartContract(sc);

	vm->analyze();
	vm->createScInstance();
	vm->destroy();
	/*VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);
	VmMemoryManager* mem = vm->getMemory();

	ObjectReference* ref = new(vm) ObjectReference(ObjectReference::REF_OBJ);*/

}
/*
TEST(TestVmVariableGroup, primitives){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/intlong/main.alns"));

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
*/



