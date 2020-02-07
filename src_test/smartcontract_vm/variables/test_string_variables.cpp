/*
 * test_string_variables.cpp
 *
 *  Created on: 2020/02/03
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"

#include "base_io_stream/FileInputStream.h"


using namespace alinous;


TEST_GROUP(TestStringVariablesGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestStringVariablesGroup, stringMemberVariable){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/variables/resources/string/main.alns"));

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
