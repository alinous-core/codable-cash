/*
 * test_insert.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"
using namespace alinous;
//using namespace codablecash;

TEST_GROUP(TestInsertGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestInsertGroup, case01) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestInsertGroup, case02) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case02/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestInsertGroup, case03_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case03_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exName = ex->getClassName();
	bool bl = exName->equals(&DatabaseExceptionClassDeclare::NAME);
	CHECK(bl)
}

TEST(TestInsertGroup, case04_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case04_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exName = ex->getClassName();
	bool bl = exName->equals(&DatabaseExceptionClassDeclare::NAME);
	CHECK(bl)
}

TEST(TestInsertGroup, case05_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case05_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exName = ex->getClassName();
	bool bl = exName->equals(&DatabaseExceptionClassDeclare::NAME);
	CHECK(bl)
}

TEST(TestInsertGroup, case06_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case06_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)
}

TEST(TestInsertGroup, case07_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/insert/case07_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	const UnicodeString* exName = ex->getClassName();
	bool bl = exName->equals(&DatabaseExceptionClassDeclare::NAME);
	CHECK(bl)
}

