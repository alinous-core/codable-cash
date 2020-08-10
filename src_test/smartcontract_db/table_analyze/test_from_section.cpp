/*
 * test_from_section.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "compiler/SmartContractParser.h"
#include "alinous_lang/AlinousLang.h"

#include "sql_dml_parts/SQLFrom.h"

#include "sc_analyze/AnalyzeContext.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/TablesHolder.h"

TEST_GROUP(TestFromSectionGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestFromSectionGroup, list01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/from/from01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SQLFrom* from = lang->sqlFrom(); __STP(from);
		CHECK(!parser.hasError())

		AbstractJoinPart* part = from->getTablePart();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		part->preAnalyze(actx);
		part->analyzeTypeRef(actx);
		part->analyze(actx);

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		part->init(vm);
		part->interpret(vm);

		TablesHolder* tableHolder = planner->getTablesHolder();
		if(!tableHolder->isEmpty()){
			AbstractScanTableTarget* target = tableHolder->pop();
			tableHolder->addScanTarget(target);
		}
		const UnicodeString* str = tableHolder->toString();

		UnicodeString ans(L"table1 AS t1, public.table2, table3");
		CHECK(ans.equals(str))
	}
}

TEST(TestFromSectionGroup, join01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	const File* projectFolder = this->env->getProjectRoot();
	_ST(File, sourceFile, projectFolder->get(L"src_test/smartcontract_db/table_analyze/resources/from/join01.alns"))
	{
		SmartContractParser parser(sourceFile);
		AlinousLang* lang = parser.getDebugAlinousLang();

		SQLFrom* from = lang->sqlFrom(); __STP(from);
		CHECK(!parser.hasError())

		AbstractJoinPart* part = from->getTablePart();

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		part->preAnalyze(actx);
		part->analyzeTypeRef(actx);
		part->analyze(actx);

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		part->init(vm);
		part->interpret(vm);

		TablesHolder* tableHolder = planner->getTablesHolder();
		if(!tableHolder->isEmpty()){
			AbstractScanTableTarget* target = tableHolder->pop();
			tableHolder->addScanTarget(target);
		}
		const UnicodeString* str = tableHolder->toString();

		UnicodeString ans(L"table1 LEFT JOIN table2");
		CHECK(ans.equals(str))
	}
}
