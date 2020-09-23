/*
 * test_exec_alter_modify.cpp
 *
 *  Created on: 2020/09/13
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "../toolkit/TestDbSchema01.h"

#include "sc_analyze/AnalyzeContext.h"

#include "engine/CodableDatabase.h"

#include "schema/SchemaManager.h"

#include "table/CdbTable.h"

#include "table/CdbTableColumn.h"

#include "table/CdbTableIndex.h"
TEST_GROUP(TestExecAlterMofdifyGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};


// ALTER TABLE test_table MODIFY email_id varchar(255) not null unique default 0;
TEST(TestExecAlterMofdifyGroup, case01){
	TestDbSchema01 schem(this->env);
	schem.init();

	VirtualMachine* vm = schem.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_alter/resources/exec_alter/case01.alns"))
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

	CdbTableColumn* col = schem.getColumn(L"test_table", L"email_id");
	CHECK(col->isUnique() == true);
	CHECK(col->isNotnull() == true);

	CdbTableIndex* index = schem.getIndex(L"test_table", L"email_id");
	CHECK(index->isUnique());

	IndexStore* idx = schem.getIndexStore(L"test_table", L"email_id");
	CHECK(idx != nullptr);

}


