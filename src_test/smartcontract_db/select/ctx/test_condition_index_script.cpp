/*
 * test_condition_index_script.cpp
 *
 *  Created on: 2020/11/07
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"


#include "base/StackRelease.h"

#include "base_io/File.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "engine/compiler/SmartContractParser.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "alinous_lang/AlinousLang.h"
#include "smartcontract_db/toolkit/TestDbSchema01.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

#include "scan_select/scan_table/TableScanTarget.h"

#include "vm/VmSelectPlannerSetter.h"

//using namespace codablecash;

TEST_GROUP(TestConditionIndexScriptGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

static AbstractSQLExpression* parse(const File* sourceFile);

AbstractSQLExpression* parse(const File* sourceFile){
	SmartContractParser parser(sourceFile);
	AlinousLang* lang = parser.getDebugAlinousLang();

	return lang->sqlExpression();
}

TEST(TestConditionIndexScriptGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/ctx/resources/conditions/and01.alns"))

	{
		AbstractSQLExpression* cond = parse(sourceFile); __STP(cond);

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		cond->preAnalyze(actx);
		cond->analyzeTypeRef(actx);
		cond->analyze(actx);

		cond->init(vm);

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table"); __STP(target);
	}
}
