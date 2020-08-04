/*
 * test_select_arithmetic_contition.cpp
 *
 *  Created on: 2020/07/31
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base_io/File.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

#include "sql_dml_parts/SQLWhere.h"

#include "sc_analyze/AnalyzeContext.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"

#include "scan_condition/RootScanCondition.h"


using namespace alinous;

TEST_GROUP(TestSelectArithmeticConditionGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestSelectArithmeticConditionGroup, add01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/arithmetic/where01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SQLWhere* where = lang->sqlWhere(); __STP(where);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		where->preAnalyze(actx);
		where->analyzeTypeRef(actx);
		where->analyze(actx);

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		where->init(vm);

		where->interpret(vm);

		ConditionsHolder* holder = planner->getConditions();
		RootScanCondition* root = holder->getRoot();
		const UnicodeString* str = root->toStringCode();

		UnicodeString sql(L"id = 1 + 2 - 3");
		CHECK(sql.equals(str));
	}
}

TEST(TestSelectArithmeticConditionGroup, add02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/arithmetic/where02.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SQLWhere* where = lang->sqlWhere(); __STP(where);
		CHECK(!parser.hasError())

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		where->preAnalyze(actx);
		where->analyzeTypeRef(actx);
		where->analyze(actx);

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		where->init(vm);

		where->interpret(vm);

		ConditionsHolder* holder = planner->getConditions();
		RootScanCondition* root = holder->getRoot();
		const UnicodeString* str = root->toStringCode();

		UnicodeString sql(L"public.test_table.id = 10 * 20 / 5 % 10");
		CHECK(sql.equals(str));
	}
}
