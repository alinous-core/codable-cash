/*
 * test_index_resolver_script.cpp
 *
 *  Created on: 2020/12/09
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/File.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "engine/compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "../../toolkit/TestDbSchemaBase.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/TablesHolder.h"
#include "scan_select/scan_planner/base/ConditionsHolder.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/index/TableIndexDetector.h"

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "scan_select/scan_condition/base/RootScanCondition.h"
#include "scan_select/scan_condition/base/AbstractScanConditionElement.h"
#include "scan_select/scan_condition/base/AbstractScanCondition.h"
#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_table/TableScanTarget.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

TEST_GROUP(TestIndexResolverScriptGroup) {
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
UnicodeString* getCandidate(const File* sourceFile, VirtualMachine* vm, TestDbSchemaBase& tester){
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

	IndexResolver resolver(tester.getDatabase());
	resolver.analyze(candidate);

	AbstractColumnsIndexWrapper* w = resolver.getResult();

	const UnicodeString* s = w->toCodeString();

	return new UnicodeString(s);
}

TEST(TestIndexResolverScriptGroup, case01){

}
