/*
 * test_transaction_fw.cpp
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/vm_trx/VmTransactionHandlerException.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

using namespace alinous;

TEST_GROUP(TestTransactionFwGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestTransactionFwGroup, caseException){
	testException<VmTransactionHandlerException>();
}

TEST(TestTransactionFwGroup, case01){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/engine/resources/trx/case01/", projectFolder, this->env);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestTransactionFwGroup, case02){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/engine/resources/trx/case02/", projectFolder, this->env);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestTransactionFwGroup, case03_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/engine/resources/trx/case03_err/", projectFolder, this->env);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* e = util.vm->getUncaughtException(); __STP(e);
	CHECK(e != nullptr)

	const UnicodeString* exname = e->getClassName();
	CHECK(exname->equals(&DatabaseExceptionClassDeclare::NAME))
}

TEST(TestTransactionFwGroup, case04_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/engine/resources/trx/case04_err/", projectFolder, this->env);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* e = util.vm->getUncaughtException(); __STP(e);
	CHECK(e != nullptr)

	const UnicodeString* exname = e->getClassName();
	CHECK(exname->equals(&DatabaseExceptionClassDeclare::NAME))
}

TEST(TestTransactionFwGroup, case05_err){
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/engine/resources/trx/case05_err/", projectFolder, this->env);

	util.loadAllFiles();
	util.setMain(L"test.fw", L"SmartContract", L"main");

	bool result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* e = util.vm->getUncaughtException(); __STP(e);
	CHECK(e != nullptr)

	const UnicodeString* exname = e->getClassName();
	CHECK(exname->equals(&DatabaseExceptionClassDeclare::NAME))
}

