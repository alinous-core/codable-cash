/*
 * test_scan_columns_exp_part.cpp
 *
 *  Created on: 2020/08/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base/UnicodeString.h"

#include "base_io/File.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "compiler/SmartContractParser.h"

#include "sql_dml/SelectStatement.h"

#include "sql_dml_parts/SQLSelectTargetList.h"

#include "sc_analyze/AnalyzeContext.h"

#include "scan_planner/SelectScanPlanner.h"

#include "alinous_lang/AlinousLang.h"

#include "scan_columns/ScanColumnHolder.h"

#include "instance_exception/ExceptionInterrupt.h"

#include "scan_columns_exp/InExpressionScanColumnTarget.h"

#include "engine/CdbException.h"
using namespace codablecash;

TEST_GROUP(TestScanColumnsExpPartGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestScanColumnsExpPartGroup, betweeen01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select04.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"col1 BETWEEN 1 AND 10");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, function01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select05.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"count(col1, col2)");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, function02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select06.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"count(*)");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, inNull01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select07.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"col1 IS NOT NULL");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, like01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select08.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"col1 LIKE '%test%' ESCAPE '%'");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, placeholder01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select09.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		//selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"func01(${})");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, in01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select10.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		selectList->init(vm);
		selectList->interpret(vm);

		ScanColumnHolder* holder = planner->getColumnHolder();
		UnicodeString* str = holder->toCodeString(); __STP(str);

		UnicodeString ans(L"col1 IN (1, 2, 3)");
		CHECK(str->equals(ans));
	}
}

TEST(TestScanColumnsExpPartGroup, in_cast_error){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/columns_exp/select10.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SelectStatement* stmt = lang->selectStatement(); __STP(stmt);
		CHECK(!parser.hasError())

		SQLSelectTargetList* selectList = stmt->getSQLSelectTargetList();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		selectList->preAnalyze(actx);
		selectList->analyzeTypeRef(actx);
		selectList->analyze(actx);

		CdbException* ex = nullptr;
		try{
			InExpressionScanColumnTarget::castToExpressionListScanColumnTarget(nullptr, vm, stmt);
		}
		catch(CdbException* e){
			ex = e;
		}

		delete ex;

	}
}
