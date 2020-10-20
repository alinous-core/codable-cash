/*
 * test_create_table_error.cpp
 *
 *  Created on: 2020/10/11
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "base_io/File.h"

#include "smartcontract_db/toolkit/TestDbSchema01.h"

#include "vm/VirtualMachine.h"

#include "engine/compiler/SmartContractParser.h"
#include "alinous_lang/AlinousLang.h"

#include "lang_sql/sql_ddl/DropTableStatement.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "ext_binary/ExtExceptionObject.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "smartcontract_db/toolkit/TestDbSchemaBase.h"
#include "engine/sc_analyze/ValidationError.h"

using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestCreateTableErrorGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestCreateTableErrorGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_ddl/resources/create_err/case01.alns"))
	{
		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

TEST(TestCreateTableErrorGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_ddl/resources/create_err/case02.alns"))
	{
		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

TEST(TestCreateTableErrorGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_ddl/resources/create_err/case03.alns"))
	{
		bool result = tester.execDDL(sourceFile);
		CHECK(!result);

		result = tester.getVm()->hasAnalyzeError(ValidationError::DB_CREATE_TABLE_COLUMN_DUPLICATED_NAME);
		CHECK(result);
	}
}

