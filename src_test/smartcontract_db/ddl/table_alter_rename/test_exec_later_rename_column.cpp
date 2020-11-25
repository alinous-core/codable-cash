/*
 * test_exec_later_rename_column.cpp
 *
 *  Created on: 2020/10/05
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

TEST_GROUP(TestExecAlterRenameColumnGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 * ALTER TABLE test_table RENAME id TO id2;
 */
TEST(TestExecAlterRenameColumnGroup, renameColumn01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_rename/resources/exec_rename/renameColumn01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);
	}

	{
		CdbTableIndex* index = tester.getIndex(L"test_table", L"id2");
		CHECK(index != nullptr);

		IndexStore* idxStore = tester.getIndexStore(L"public", L"test_table", L"id2");
		CHECK(idxStore != nullptr);
	}

	tester.reloadDb();

	{
		CdbTableIndex* index = tester.getIndex(L"test_table", L"id2");
		CHECK(index != nullptr);

		IndexStore* idxStore = tester.getIndexStore(L"public", L"test_table", L"id2");
		CHECK(idxStore != nullptr);
	}
}

/**
 * column already exists
 * ALTER TABLE test_table RENAME id TO email_id;
 */
TEST(TestExecAlterRenameColumnGroup, renameColumn02){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_rename/resources/exec_rename/renameColumn02.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);
	}

	const ExtExceptionObject* ex = tester.checkUncaughtException();
	CHECK(ex != nullptr);

	CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
}

/**
 * last column does not exist
 * ALTER TABLE test_table RENAME id2 TO id3;
 */
TEST(TestExecAlterRenameColumnGroup, renameColumn03){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/ddl/table_alter_rename/resources/exec_rename/renameColumn03.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		AlterTableStatement* stmt = lang->alterTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);
	}

	const ExtExceptionObject* ex = tester.checkUncaughtException();
	CHECK(ex != nullptr);

	CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
}

