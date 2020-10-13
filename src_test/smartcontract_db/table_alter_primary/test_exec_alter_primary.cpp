/*
 * test_exec_alter_primary.cpp
 *
 *  Created on: 2020/09/24
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

#include "schema_table/schema/SchemaManager.h"

#include "schema_table/table/CdbTable.h"
#include "schema_table/table/CdbTableColumn.h"
#include "schema_table/table/CdbTableIndex.h"

#include "../toolkit_alter/TestDbSchemaAlterTextUnique01.h"
#include "ext_binary/ExtExceptionObject.h"

#include "transaction_exception/DatabaseExceptionClassDeclare.h"
TEST_GROUP(TestExecAlterPrimaryGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


/**
 * primary key is unique
 */
TEST(TestExecAlterPrimaryGroup, dropPrimaryKey01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/dropPrimaryKey01.alns"))
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

	// again
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
 * primary key is not unique
 */
TEST(TestExecAlterPrimaryGroup, dropPrimaryKey02){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/dropPrimaryKey01.alns"))
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

	CdbTableIndex* index = tester.getPrimaryKey(L"test_table");
	CHECK(index == nullptr);
}

/**
 *	add primary key(unique) after drop
 *	ALTER TABLE test_table ADD PRIMARY KEY(id);
 */
TEST(TestExecAlterPrimaryGroup, addPrimaryKey01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	// DROP FIRST
	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/dropPrimaryKey01.alns"))
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
	}

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/addPrimaryKey01.alns"))
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

	CdbTableIndex* index = tester.getPrimaryKey(L"test_table");
	CHECK(index != nullptr);
}

/**
 *	add primary key(not unique) after drop
 *	ALTER TABLE test_table ADD PRIMARY KEY(id);
 */
TEST(TestExecAlterPrimaryGroup, addPrimaryKey02){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	// DROP FIRST
	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/dropPrimaryKey01.alns"))
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
	}

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/addPrimaryKey01.alns"))
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

	CdbTableIndex* index = tester.getPrimaryKey(L"test_table");
	CHECK(index != nullptr);
}

/**
 * column does not exists
 * ALTER TABLE test_table ADD PRIMARY KEY(id2);
 */
TEST(TestExecAlterPrimaryGroup, addPrimaryKey03_err){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();
	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/dropPrimaryKey01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);
	}

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/addPrimaryKey03_err.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}

/**
 * primary key already exists
 */
TEST(TestExecAlterPrimaryGroup, addPrimaryKey04_err){
	TestDbSchemaAlterTextUnique01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	{
		const File* projectFolder = this->env->getProjectRoot();
		_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_primary/resources/exec_primary/addPrimaryKey01.alns"))

		bool result = tester.execDDL(sourceFile);
		CHECK(result);

		const ExtExceptionObject* ex = tester.checkUncaughtException();
		CHECK(ex != nullptr);

		CHECK(ex->getClassName()->equals(&DatabaseExceptionClassDeclare::NAME));
	}
}
