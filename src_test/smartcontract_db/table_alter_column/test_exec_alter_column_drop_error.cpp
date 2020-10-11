/*
 * test_exec_alter_column_drop_error.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "../toolkit/TestDbSchema01.h"
#include "../toolkit_alter/TestDbSchemaAlter01.h"
#include "../toolkit_alter/TestDbSchemaAlter02.h"
#include "../toolkit_alter/TestDbSchemaAlter03.h"

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "ext_binary/ExtExceptionObject.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

TEST_GROUP(TestExecAlterColumnDropErrorGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 * column does not exists
 *	ALTER TABLE test_table DROP email_id2;
 */
TEST(TestExecAlterColumnDropErrorGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_column/resources/drop_error/case01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * drop primary key
 * ALTER TABLE test_table DROP id;
 */
TEST(TestExecAlterColumnDropErrorGroup, case02){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_column/resources/drop_error/case02.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}
