/*
 * test_exec_alter_modify_unique.cpp
 *
 *  Created on: 2020/09/30
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

#include "../toolkit_alter/TestDbSchemaAlterText01.h"
using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestExecAlterMofdifyUniqueGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


/**
 * Add unique error
 * ALTER TABLE test_table MODIFY email_id int unique;
 */
TEST(TestExecAlterMofdifyUniqueGroup, case01){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert03();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter/case11.alns"))
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
 * set primary key unique
 * ALTER TABLE test_table MODIFY id int unique;
 *
 */
TEST(TestExecAlterMofdifyUniqueGroup, case02){
	TestDbSchemaAlterText01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_unique/case01.alns"))
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

		// check before interpret
		CdbTableIndex* pidx = nullptr;
		{
			CdbTableColumn* col = tester.getColumn(L"test_table", L"id");
			CHECK(!col->isNotnull());
			CHECK(!col->isUnique());

			pidx = tester.getPrimaryKey(L"test_table");
			CHECK(pidx != nullptr);
		}

		stmt->interpret(vm);

		// after
		{
			CdbTableIndex* pidx2 = tester.getPrimaryKey(L"test_table");
			CHECK(pidx == pidx2);
		}
	}
}

/**
 * set primary key not unique -> do not delete primary key index
 * ALTER TABLE test_table MODIFY id int;
 */
TEST(TestExecAlterMofdifyUniqueGroup, case03){
	TestDbSchemaAlter01 tester(this->env);
	tester.init(1024*10);
	tester.insert01();

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter_modify/resources/exec_alter_modify_unique/case02.alns"))
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
