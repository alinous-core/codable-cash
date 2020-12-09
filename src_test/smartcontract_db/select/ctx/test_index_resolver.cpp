/*
 * test_index_resolver.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "smartcontract_db/toolkit/TestDbSchema01.h"

#include "lang_sql/sql_expression/SQLColumnIdentifier.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"
#include "scan_select/scan_condition/params/NumericScanParam.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/TablesHolder.h"

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "vm/VmSelectPlannerSetter.h"

#include "scan_select/scan_table/TableScanTarget.h"

using namespace codablecash;

TEST_GROUP(TestIndexResolverGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestIndexResolverGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		IndexResolver resolver(tester.getDatabase());

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);
		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");


		ColumnIdentifierScanParam pid(&id);

		pid.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		resolver.analyze(candidate);

		AbstractColumnsIndexWrapper* w = resolver.getResult();

		const UnicodeString* s = w->toCodeString();
		UnicodeString ans(L"10 < id");
		CHECK(ans.equals(s));
	}
}

TEST(TestIndexResolverGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		IndexResolver resolver(tester.getDatabase());

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);
		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");


		ColumnIdentifierScanParam pid(&id);

		pid.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT_EQ); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		resolver.analyze(candidate);

		AbstractColumnsIndexWrapper* w = resolver.getResult();

		const UnicodeString* s = w->toCodeString();
		UnicodeString ans(L"10 <= id");
		CHECK(ans.equals(s));
	}
}

TEST(TestIndexResolverGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		IndexResolver resolver(tester.getDatabase());

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);
		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");


		ColumnIdentifierScanParam pid(&id);

		pid.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_LT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		resolver.analyze(candidate);

		AbstractColumnsIndexWrapper* w = resolver.getResult();

		const UnicodeString* s = w->toCodeString();
		UnicodeString ans(L"id < 10");
		CHECK(ans.equals(s));
	}
}

TEST(TestIndexResolverGroup, case04){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		IndexResolver resolver(tester.getDatabase());

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);
		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");


		ColumnIdentifierScanParam pid(&id);

		pid.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_LT_EQ); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		resolver.analyze(candidate);

		AbstractColumnsIndexWrapper* w = resolver.getResult();

		const UnicodeString* s = w->toCodeString();
		UnicodeString ans(L"id <= 10");
		CHECK(ans.equals(s));
	}
}

TEST(TestIndexResolverGroup, case05){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		IndexResolver resolver(tester.getDatabase());

		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);
		TablesHolder* tableHolder = planner->getTablesHolder();
		TableScanTarget* target = tester.getScanTarget(L"public", L"test_table");
		tableHolder->addScanTarget(target);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");


		ColumnIdentifierScanParam pid(&id);

		pid.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		resolver.analyze(candidate);

		AbstractColumnsIndexWrapper* w = resolver.getResult();

		const UnicodeString* s = w->toCodeString();
		UnicodeString ans(L"id = 10");
		CHECK(ans.equals(s));
	}
}
