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

#include "scan_select/scan_planner/base/ConditionsHolder.h"

#include "scan_select/scan_condition/base/RootScanCondition.h"

#include "scan_select/scan_planner/base/TablesHolder.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_planner/scanner/index/TableIndexDetector.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"
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

static UnicodeString* getCandidate(const File* sourceFile, VirtualMachine* vm, TestDbSchemaBase& tester);
static UnicodeString* getCandidate(const File* sourceFile, VirtualMachine* vm, TestDbSchemaBase& tester){
	AbstractSQLExpression* sqlexp = parse(sourceFile); __STP(sqlexp);

	AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
	actx->setVm(vm);

	sqlexp->preAnalyze(actx);
	sqlexp->analyzeTypeRef(actx);
	sqlexp->analyze(actx);

	sqlexp->init(vm);

	SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
	VmSelectPlannerSetter setter(vm, planner);

	TablesHolder* tableHolder = planner->getTablesHolder();
	TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
	tableHolder->addScanTarget(target);

	sqlexp->interpret(vm);

	ConditionsHolder* cholder = planner->getConditions();
	RootScanCondition* root = cholder->getRoot();

	AbstractScanConditionElement* element = cholder->pop();

	AbstractScanCondition* cond = ScanConditionCast::toAbstractScanCondition(element, vm, nullptr);
	root->addCondition(cond);
	root->analyzeConditions(vm, planner);

	FilterConditionDitector filterDetector(vm, planner);
	filterDetector.detect(target);

	AbstractScanCondition* filterCondition = filterDetector.getCondition();

	TableIndexDetector indexDetextor(vm, planner, target);
	indexDetextor.detect(filterCondition);

	AbstractIndexCandidate* candidate = nullptr;
	if(!indexDetextor.isEmpty()){
		candidate = indexDetextor.pop();
	}
	__STP(candidate);

	const UnicodeString* str = candidate->toCodeString();

	return new UnicodeString(str);
}

TEST(TestConditionIndexScriptGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/ctx/resources/conditions/and01.alns"))

	{
		UnicodeString* str = getCandidate(sourceFile, vm, tester); __STP(str);

		UnicodeString ans(L"0 <= test_table.id <= 100");
		CHECK(ans.equals(str));
	}
}
