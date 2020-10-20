/*
 * test_exec_alter_index_add_err.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "engine/compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "smartcontract_db/toolkit/TestDbSchema01.h"
#include "smartcontract_db/toolkit_alter//TestDbSchemaAlter01.h"
#include "smartcontract_db/toolkit_alter//TestDbSchemaAlter02.h"
#include "smartcontract_db/toolkit_alter//TestDbSchemaAlter03.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "ext_binary/ExtExceptionObject.h"

TEST_GROUP(TestExecAlterIndexAddErrGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 *	wrong column
 *	ALTER TABLE test_table ADD INDEX test_index(email_id12);
 */
TEST(TestExecAlterIndexAddErrGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * index with same columns exists
 */
TEST(TestExecAlterIndexAddErrGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case02.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex == nullptr);
	}

	{
		/**
		 * ALTER TABLE test_table ADD UNIQUE INDEX test_index2(email_id);
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case02_2.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * index with same name exists
 */
TEST(TestExecAlterIndexAddErrGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case02.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex == nullptr);
	}

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case03.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * use table name as index
 * ALTER TABLE test_table ADD UNIQUE INDEX test_table(id, email_id);
 */
TEST(TestExecAlterIndexAddErrGroup, case04){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case04.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * set unique to have multiple ununique records
 * ALTER TABLE test_table ADD UNIQUE INDEX test_index(email_id);
 */
TEST(TestExecAlterIndexAddErrGroup, case05){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_index/resources/add_error/case05.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}
