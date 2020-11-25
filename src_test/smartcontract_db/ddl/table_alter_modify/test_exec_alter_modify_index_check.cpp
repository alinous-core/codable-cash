/*
 * test_exec_alter_modify_index_check.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "smartcontract_db/toolkit_alter//TestDbSchemaAlterModifyIndexCheck.h"
#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "ext_binary/ExtExceptionObject.h"
using namespace codablecash;

TEST_GROUP(TestExecAlterModifyIndexCheckGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 * error thrown because of index error
 */
TEST(TestExecAlterModifyIndexCheckGroup, case01){
	TestDbSchemaAlterModifyIndexCheck tester(env);
	tester.init(1024*10);
	tester.insert01();

	{
		/**
		 * ALTER TABLE test_table ADD UNIQUE INDEX test_index(email_id, comment);
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/check_index/addIndex01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex == nullptr);
	}

	{
		/**
		 * ALTER TABLE test_table MODIFY comment int not null default 0;
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/check_index/case01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * OK case
 */
TEST(TestExecAlterModifyIndexCheckGroup, case02){
	TestDbSchemaAlterModifyIndexCheck tester(env);
	tester.init(1024*10);
	tester.insert02();

	{
		/**
		 * ALTER TABLE test_table ADD UNIQUE INDEX test_index(email_id, comment);
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/check_index/addIndex01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex == nullptr);
	}

	{
		/**
		 * ALTER TABLE test_table MODIFY comment int not null default 0;
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_modify/resources/check_index/case01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex == nullptr);
	}
}
