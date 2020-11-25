/*
 * test_create_table_script.cpp
 *
 *  Created on: 2020/05/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "vm/vm_trx/VmTransactionHandlerException.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "engine/sc_analyze/ValidationError.h"

#include "smartcontract_vm/VmTestUtils.h"

using namespace alinous;

TEST_GROUP(TestCreateTableScriptGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};


TEST(TestCreateTableScriptGroup, case01) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestCreateTableScriptGroup, case01_2) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case01_2/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}

TEST(TestCreateTableScriptGroup, case02_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case02_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::DB_TYPE_NOT_EXISTS));
}

TEST(TestCreateTableScriptGroup, case03_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case03_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::DB_NO_PRIMARY_KEY));
}

TEST(TestCreateTableScriptGroup, case04_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case04_err/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(!result)

	CHECK(util.vm->hasAnalyzeError(ValidationError::DB_LENGTH_IS_NOT_INTEGER));
}

TEST(TestCreateTableScriptGroup, case05_err) {
	const File* projectFolder = this->env->getProjectRoot();
	VmTestUtils util(L"src_test/smartcontract_db/ddl/table_ddl/resources/create/case01/", projectFolder);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)

	ExtExceptionObject* ex = util.vm->getUncaughtException(); __STP(ex);
	CHECK(ex != nullptr);

}

