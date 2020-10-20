/*
 * test_exec_alter_drop_column.cpp
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
#include "smartcontract_db/toolkit_alter/TestDbSchemaAlter01.h"
#include "smartcontract_db/toolkit_alter/TestDbSchemaAlter02.h"
#include "smartcontract_db/toolkit_alter/TestDbSchemaAlter03.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "ext_binary/ExtExceptionObject.h"

#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "schema_table/table_store/CdbStorageManager.h"

TEST_GROUP(TestExecAlterColumnDropGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

TEST(TestExecAlterColumnDropGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	SchemaManager* schemaManager = tester.getSchemaManager();
	CdbStorageManager* storageManager = tester.getStorageManager();

	{
		/**
		 * ALTER TABLE test_table ADD INDEX test_index(id, email_id);
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_column/resources/drop/case01_1.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);
	}

	{
		/**
		 * ALTER TABLE test_table DROP email_id;
		 */
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_column/resources/drop/case01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		CdbTable* table = schemaManager->getTable(L"public", L"test_table");
		TableStore* store = storageManager->getTableStore(table->getOid());

		UnicodeString indexname(L"test_index");
		CdbTableIndex* idx = table->getIndexByName(&indexname);

		CHECK(idx == nullptr);
	}
}


