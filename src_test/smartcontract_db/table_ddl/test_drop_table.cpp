/*
 * test_drop_table.cpp
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "base_io/File.h"

#include "../toolkit/TestDbSchema01.h"

#include "vm/VirtualMachine.h"

#include "compiler/SmartContractParser.h"
#include "alinous_lang/AlinousLang.h"

#include "sql_ddl/DropTableStatement.h"

#include "sc_analyze/AnalyzeContext.h"
using namespace codablecash;
using namespace alinous;

TEST_GROUP(TestDropTableGroup) {
	TEST_SETUP() {
		env->setup();
	}
	TEST_TEARDOWN() {
		env->teardown();
	}
};

/**
 *	DROP TABLE test_table;
 */
TEST(TestDropTableGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024*10);

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table/resources/droptable/case01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		DropTableStatement* stmt = lang->dropTableStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		stmt->preAnalyze(actx);
		stmt->analyzeTypeRef(actx);
		stmt->analyze(actx);

		stmt->interpret(vm);
	}
}
