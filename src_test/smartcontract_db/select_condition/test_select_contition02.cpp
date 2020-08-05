/*
 * test_select_contition02.cpp
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base_io/File.h"
#include "base/UnicodeString.h"

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

TEST_GROUP(TestSelectConditionGroup02) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestSelectConditionGroup02, IsNull01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select_condition/resources/conditions/grp03/where01.alns"))
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

		UnicodeString sql(L"id IS NULL");
		CHECK(sql.equals(str));
	}
}

TEST(TestSelectConditionGroup02, IsNull02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select_condition/resources/conditions/grp03/where02.alns"))
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

		UnicodeString sql(L"id IS NOT NULL");
		CHECK(sql.equals(str));
	}
}

TEST(TestSelectConditionGroup02, PlaceHolder01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select_condition/resources/conditions/grp03/where03.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SQLWhere* where = lang->sqlWhere(); __STP(where);
		CHECK(!parser.hasError())

		AbstractSQLExpression* exp = where->getExp();
		SQLEqualityExpression* eqExp = dynamic_cast<SQLEqualityExpression*>(exp);
		exp = eqExp->getRight();
		exp->setExecutable(false);

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

		UnicodeString sql(L"id = ${}");
		CHECK(sql.equals(str));
	}
}
