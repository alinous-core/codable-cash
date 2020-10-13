/*
 * test_call_maininst.cpp
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "ext_arguments/NullArgument.h"

#include "engine/sc_analyze_functions/VTableRegistory.h"

#include "ext_binary/AbstractExtObject.h"
#include "ext_binary/ExtClassObject.h"
#include "ext_binary/ExtPrimitiveObject.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/VmClassInstance.h"

#include "../VmTestUtils.h"
#include "ext_arguments/NumericArgument.h"

#include "vm/exceptions.h"

#include "ext_arguments/StringArgument.h"

#include "ext_arguments/BoolArgument.h"
using namespace alinous;


TEST_GROUP(TestCallMainInstGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestCallMainInstGroup, extArguments){
	AnalyzedType at(AnalyzedType::TYPE_BOOL);
	NullArgument nullArg(&at);
}

TEST(TestCallMainInstGroup, testException01){
	testException<VmMethodNotFoundException>();
}

TEST(TestCallMainInstGroup, callMainMethod){
	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case01/main.alns"));

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

TEST(TestCallMainInstGroup, callMainMethod2){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	args.addElement(new NumericArgument(10, AnalyzedType::TYPE_INT));
	util.vm->interpret(&method, &args);

	ExtClassObject* classObject = util.getMainExtObject(); __STP(classObject);

	int count = VmTestUtils::getIntMemberValue(classObject, L"count");
	CHECK(count == 10)
}

TEST(TestCallMainInstGroup, callMainMethod2_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case02/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test2");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	args.addElement(new NumericArgument(10, AnalyzedType::TYPE_INT));

	VmMethodNotFoundException* ex = nullptr;
	try{
		util.vm->interpret(&method, &args);
	}catch(VmMethodNotFoundException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestCallMainInstGroup, callMainMethod3){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case03/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	UnicodeString hello(L"Hello World");
	args.addElement(new StringArgument(&hello));
	util.vm->interpret(&method, &args);
}

TEST(TestCallMainInstGroup, callMainMethod4){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case04/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	args.addElement(new BoolArgument(true));

	util.vm->interpret(&method, &args);

	ExtClassObject* classObject = util.getMainExtObject(); __STP(classObject);
	bool bl = VmTestUtils::getBoolMemberValue(classObject, L"count");
	CHECK(bl == true)
}

TEST(TestCallMainInstGroup, callMainMethod5){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case05/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	AnalyzedType at(AnalyzedType::TYPE_STRING);
	args.addElement(new NullArgument(&at));

	util.vm->interpret(&method, &args);

	ExtClassObject* classObject = util.getMainExtObject(); __STP(classObject);
	const UnicodeString* str = VmTestUtils::getStringMemberValue(classObject, L"str");

	CHECK(str == nullptr)
}

TEST(TestCallMainInstGroup, callMainMethod6){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_vm/method_invoke/resources/callMainMethod/case06/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	UnicodeString method(L"test");
	ArrayList<AbstractFunctionExtArguments> args;
	args.setDeleteOnExit();

	args.addElement(new NumericArgument(10, AnalyzedType::TYPE_BYTE));
	args.addElement(new NumericArgument(11, AnalyzedType::TYPE_SHORT));
	args.addElement(new NumericArgument(12, AnalyzedType::TYPE_CHAR));
	args.addElement(new NumericArgument(13, AnalyzedType::TYPE_LONG));

	util.vm->interpret(&method, &args);

	ExtClassObject* classObject = util.getMainExtObject(); __STP(classObject);

	int64_t num = VmTestUtils::getByteMemberValue(classObject, L"b");
	CHECK(num == 10);

	num = VmTestUtils::getByteMemberValue(classObject, L"s");
	CHECK(num == 11);

	num = VmTestUtils::getByteMemberValue(classObject, L"c");
	CHECK(num == 12);

	num = VmTestUtils::getByteMemberValue(classObject, L"l");
	CHECK(num == 13);
}


