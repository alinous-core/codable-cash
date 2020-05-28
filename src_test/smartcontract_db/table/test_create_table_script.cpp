/*
 * test_create_table_script.cpp
 *
 *  Created on: 2020/05/25
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"


#include "ext_binary/ExtClassObject.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm_trx/VmTransactionHandlerException.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

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
	VmTestUtils util(L"src_test/smartcontract_db/table/resources/create/case01/", projectFolder, this->env);

	bool result = util.loadAllFiles();
	CHECK(result)

	util.setMain(L"test.fw", L"SmartContract", L"main");

	result = util.analyze();
	CHECK(result)

	result = util.createInstance();
	CHECK(result)
}
