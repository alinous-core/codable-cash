/*
 * test_join_scan_cost.cpp
 *
 *  Created on: 2020/10/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "smartcontract_db/toolkit/TestDbSchema01.h"
#include "scan_select/scan_planner/scanner/join/JoinCandidate.h"

#include "lang_sql/sql_expression/SQLColumnIdentifier.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "scan_select/scan_planner/scanner/join/JoinMultipleCandidate.h"
#include "scan_select/scan_planner/scanner/join/JoinOrCandidate.h"

#include "scan_select/scan_table/TableScanTarget.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "scan_select/scan_planner/analyze/ScanTargetNameResolver.h"
#include "scan_select/scan_planner/analyze/AnalyzedScanPlan.h"

using namespace codablecash;

TEST_GROUP(TestJoinScanCostGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestJoinScanCostGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		TableScanTarget target_test_table(L"public", L"test_table");
		target_test_table.resolveTable(vm, planner);

		TableScanTarget target_emails(L"public", L"emails");
		UnicodeString alias("em");
		target_emails.setAlias(&alias);
		target_emails.resolveTable(vm, planner);


		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier em_email_id(nullptr, L"em", L"email_id");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pem_email_id(&em_email_id);

		pid.analyzeConditions(vm, planner);
		pem_email_id.analyzeConditions(vm, planner);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pem_email_id);
		int cost = candidate.getOverHeadScore(&target_test_table, &target_emails);
		CHECK(cost == 1);

		cost = candidate.getOverHeadScore(&target_emails, &target_test_table);
		CHECK(cost == 1);
	}
}

TEST(TestJoinScanCostGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		TableScanTarget target_test_table(L"public", L"test_table");
		target_test_table.resolveTable(vm, planner);

		TableScanTarget target_emails(L"public", L"emails");
		UnicodeString alias("em");
		target_emails.setAlias(&alias);
		target_emails.resolveTable(vm, planner);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier em_email(nullptr, L"em", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pem_email(&em_email);

		pid.analyzeConditions(vm, planner);
		pem_email.analyzeConditions(vm, planner);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pem_email);
		int cost = candidate.getOverHeadScore(&target_test_table, &target_emails);
		CHECK(cost == 1000);
	}
}

TEST(TestJoinScanCostGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		TableScanTarget target_test_table(L"public", L"test_table");
		target_test_table.resolveTable(vm, planner);

		TableScanTarget target_emails(L"public", L"emails");
		UnicodeString alias("em");
		target_emails.setAlias(&alias);
		target_emails.resolveTable(vm, planner);

		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier em_email_id(nullptr, L"em", L"email_id");
		SQLColumnIdentifier em_email(nullptr, L"em", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pem_email_id(&em_email_id);
		ColumnIdentifierScanParam pem_email(&em_email);

		pid.analyzeConditions(vm, planner);
		pem_email_id.analyzeConditions(vm, planner);
		pem_email.analyzeConditions(vm, planner);

		JoinCandidate candidate1(JoinCandidate::INNER, &pid, &pem_email_id);
		JoinCandidate candidate2(JoinCandidate::INNER, &pid, &pem_email);


		AbstractJoinCandidate* c3 = candidate1.multiply(&candidate2); __STP(c3);

		JoinMultipleCandidate* mulCandidate = dynamic_cast<JoinMultipleCandidate*>(c3);

		int cost = mulCandidate->getOverHeadScore(&target_test_table, &target_emails);
		CHECK(cost == 1);
	}
}

