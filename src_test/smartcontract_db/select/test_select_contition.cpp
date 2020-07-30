/*
 * test_select_contition.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "sc/SmartContract.h"

#include "sc_analyze/AnalyzeContext.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"
#include "scan_planner/SelectScanPlanner.h"


using namespace alinous;

TEST_GROUP(TestSelectConditionGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestSelectConditionGroup, case01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/grp01/where01.alns"))
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
	}
}

TEST(TestSelectConditionGroup, case02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/grp01/where02.alns"))
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
	}
}

TEST(TestSelectConditionGroup, case03){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/grp01/where03.alns"))

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
	}
}

TEST(TestSelectConditionGroup, case04){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/grp01/where04.alns"))

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
	}
}

TEST(TestSelectConditionGroup, case05_not){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/select/resources/conditions/grp02/where01.alns"))

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
	}
}
