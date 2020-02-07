/*
 * test_call_maininst.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_arguments/NullArgument.h"

#include "sc_analyze_functions/VTableRegistory.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "sc_analyze/AnalyzeContext.h"

#include "instance/VmClassInstance.h"


using namespace alinous;


TEST_GROUP(TestCallMainInstGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};


TEST(TestCallMainInstGroup, callMainMethod){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/main.alns"));

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
		vm->interpret(&mainMethod);
	}

	AnalyzeContext* actx = vm->getSmartContract()->getAnalyzeContext();
	VTableRegistory* reg = actx->getVtableRegistory();

	UnicodeString name(L"name");
	AbstractExtObject* extObj = mainInst->toClassExtObject(&name, reg); __STP(extObj);

	ExtClassObject* classObject = dynamic_cast<ExtClassObject*>(extObj);

	UnicodeString strCount(L"count");
	ExtPrimitiveObject* obj = classObject->getExtPrimitiveObject(&strCount);
	int32_t count = obj->getIntValue();

	CHECK(count == 1);

	vm->destroy();

}

TEST(TestCallMainInstGroup, extArguments){
	NullArgument nullArg;
}

