/*
 * test_variables.cpp
 *
 *  Created on: 2019/11/16
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "instance/instance_ref/VmRootReference.h"
using namespace alinous;


TEST_GROUP(TestVmVariableGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmVariableGroup, abstractFuncs){
	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);

	VmRootReference* ref = new(vm) VmRootReference(vm);__STP(ref);
	CHECK(ref->isPrimitive() == false);
	ref->substitute(nullptr, nullptr);
}

TEST(TestVmVariableGroup, baseToExtObject){
	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);

	VmRootReference* ref = new(vm) VmRootReference(vm);__STP(ref);
	AbstractExtObject* ext = ref->toClassExtObject(nullptr, nullptr);
	CHECK(ext == nullptr);
}

TEST(TestVmVariableGroup, basegetReferences){
	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);

	VmRootReference* ref = new(vm) VmRootReference(vm);__STP(ref);
	const VMemList<AbstractReference>* list = ref->getReferences();
	CHECK(list == nullptr);
}

TEST(TestVmVariableGroup, baseIsReference){
	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);

	VmRootReference* ref = new(vm) VmRootReference(vm);__STP(ref);
	CHECK(ref->isReference() == true);
}

TEST(TestVmVariableGroup, baseIsReferenceCmp){
	VirtualMachine* vm = new VirtualMachine(1024*1024); __STP(vm);

	VmRootReference* ref1 = new(vm) VmRootReference(vm);__STP(ref1);
	VmRootReference* ref2 = new(vm) VmRootReference(vm);__STP(ref2);

	CHECK(ref1->valueCompare(ref2) == 0);
}


TEST(TestVmVariableGroup, primitives){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/intlong/main.alns"));

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

