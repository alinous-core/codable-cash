/*
 * test_exec_alter_index_add_err.cpp
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

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

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
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_index/resources/add_error/case01.alns"))

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

/**
 * index with same name exists
 */



/**
 * set unique to have multiple records
 */

