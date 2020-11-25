/*
 * test_cast_err.cpp
 *
 *  Created on: 2020/08/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "smartcontract_vm/VmTestUtils.h"
#include "engine/sc/SmartContract.h"

#include "engine/sc/CompilationUnit.h"

#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/MethodDeclare.h"

#include "base/ArrayList.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "instance/instance_exception/ExceptionInterrupt.h"

#include "vm/VirtualMachine.h"

using namespace codablecash;

TEST_GROUP(TestScanConditionCastErrorGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestScanConditionCastErrorGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/select/select_condition/resources/cast_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	CompilationUnit* unit = util.sc->getCompilationUnit(0);
	ClassDeclare* clazz = unit->getClassDeclare(0);
	ArrayList<MethodDeclare>* methods = clazz->getMethods();
	MethodDeclare* m = methods->get(0);

	ExceptionInterrupt* ex = nullptr;
	try{
		ScanConditionCast::toAbstractScanCondition(nullptr, util.vm, m);
	}
	catch(ExceptionInterrupt* e){
		ex = e;
		util.vm->checkUncaughtException();
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestScanConditionCastErrorGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/select/select_condition/resources/cast_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	CompilationUnit* unit = util.sc->getCompilationUnit(0);
	ClassDeclare* clazz = unit->getClassDeclare(0);
	ArrayList<MethodDeclare>* methods = clazz->getMethods();
	MethodDeclare* m = methods->get(0);

	ExceptionInterrupt* ex = nullptr;
	try{
		ScanConditionCast::toIValueProvider(nullptr, util.vm, m);
	}
	catch(ExceptionInterrupt* e){
		ex = e;
		util.vm->checkUncaughtException();
	}

	CHECK(ex != nullptr)
	delete ex;
}

TEST(TestScanConditionCastErrorGroup, case03){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/select/select_condition/resources/cast_err/", projectFolder);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	CompilationUnit* unit = util.sc->getCompilationUnit(0);
	ClassDeclare* clazz = unit->getClassDeclare(0);
	ArrayList<MethodDeclare>* methods = clazz->getMethods();
	MethodDeclare* m = methods->get(0);

	ExceptionInterrupt* ex = nullptr;
	try{
		ScanConditionCast::toExpressionList(nullptr, util.vm, m);
	}
	catch(ExceptionInterrupt* e){
		ex = e;
		util.vm->checkUncaughtException();
	}

	CHECK(ex != nullptr)
	delete ex;
}
