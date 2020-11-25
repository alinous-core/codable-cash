/*
 * test_index_conditions.cpp
 *
 *  Created on: 2020/11/03
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"
#include "smartcontract_db/toolkit/TestDbSchema01.h"

#include "lang_sql/sql_expression/SQLColumnIdentifier.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"
#include "scan_select/scan_condition/params/NumericScanParam.h"
#include "scan_select/scan_condition/params/StringScanParam.h"

#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/OrIndexCandidate.h"

#include "base/StackRelease.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

#include "vm/VmSelectPlannerSetter.h"
using namespace codablecash;

TEST_GROUP(TestIndexConditionGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestIndexConditionGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		ColumnIdentifierScanParam pid(&id);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);

		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		int s = candidate->size();
		CHECK(s == 1);

		CHECK(candidate->get(0) == candidate);

		CHECK(candidate->getCandidateType() == IndexCandidate::IndexType::RANGE_GT);
	}
}

TEST(TestIndexConditionGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier name(L"public", L"test_table", L"name");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pname(&name);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);

		NumericScanParam numParam(10);
		candidate->setValue(&numParam);


		IndexCandidate* candidate2 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate2);
		candidate2->setColumn(&pname);

		StringScanParam strParam2(L"test");
		candidate2->setValue(&strParam2);

		AbstractIndexCandidate* cd = candidate->multiply(candidate2); __STP(cd);

		AbstractIndexCandidate* cd2 = cd->copy(); __STP(cd2);
		CHECK(cd2->getCandidateType() == IndexCandidate::IndexType::AND);

		const UnicodeString* str = cd2->toCodeString();
		UnicodeString ans(L"public.test_table.id > 10 AND public.test_table.name = 'test'");
		CHECK(ans.equals(str));
	}
}

TEST(TestIndexConditionGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier name(L"public", L"test_table", L"name");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pname(&name);
		ColumnIdentifierScanParam pemail_id(&email_id);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		IndexCandidate* candidate2 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate2);
		candidate2->setColumn(&pname);
		StringScanParam strParam2(L"test");
		candidate2->setValue(&strParam2);

		IndexCandidate* candidate3 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate3);
		candidate3->setColumn(&pemail_id);
		NumericScanParam numParam2(10);
		candidate3->setValue(&numParam2);


		AbstractIndexCandidate* cd = candidate->multiply(candidate2); __STP(cd);
		CHECK(cd->getCandidateType() == IndexCandidate::IndexType::AND);
		AbstractIndexCandidateCollection* cdCol = dynamic_cast<AbstractIndexCandidateCollection*>(cd);


		AbstractIndexCandidate* cd2 = cd->multiply(candidate3); __STP(cd2);

		OrIndexCandidate orCandidate;
		orCandidate.add(cdCol);
		orCandidate.add(candidate3);

		const UnicodeString* str = orCandidate.toCodeString();
		UnicodeString ans(L"public.test_table.id > 10 AND public.test_table.name = 'test' OR public.test_table.email_id = 10");
		CHECK(ans.equals(str));

		CHECK(orCandidate.getCandidateType() == AbstractIndexCandidate::IndexType::OR);
	}
}

TEST(TestIndexConditionGroup, case04){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier name(L"public", L"test_table", L"name");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pname(&name);
		ColumnIdentifierScanParam pemail_id(&email_id);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		IndexCandidate* candidate2 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate2);
		candidate2->setColumn(&pname);
		StringScanParam strParam2(L"test");
		candidate2->setValue(&strParam2);

		IndexCandidate* candidate3 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate3);
		candidate3->setColumn(&pemail_id);
		NumericScanParam numParam2(10);
		candidate3->setValue(&numParam2);

		OrIndexCandidate orCandidate;
		orCandidate.add(candidate);
		orCandidate.add(candidate2);

		AbstractIndexCandidate* mul1 = orCandidate.multiply(candidate3); __STP(mul1);
		const UnicodeString* str = mul1->toCodeString();
		UnicodeString ans(L"public.test_table.id > 10 AND public.test_table.email_id = 10 OR public.test_table.name = 'test' AND public.test_table.email_id = 10");
		CHECK(ans.equals(str));

		AbstractIndexCandidate* mul2 = candidate3->multiply(&orCandidate); __STP(mul2);
		str = mul1->toCodeString();
		UnicodeString ans2(L"public.test_table.id > 10 AND public.test_table.email_id = 10 OR public.test_table.name = 'test' AND public.test_table.email_id = 10");
		CHECK(ans2.equals(str));

	}
}

TEST(TestIndexConditionGroup, case05){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier name(L"public", L"test_table", L"name");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"emails", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pname(&name);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		pid.analyzeConditions(vm, planner);
		pname.analyzeConditions(vm, planner);
		pemail_id.analyzeConditions(vm, planner);
		pemail.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		IndexCandidate* candidate2 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate2);
		candidate2->setColumn(&pname);
		StringScanParam strParam2(L"test");
		candidate2->setValue(&strParam2);

		IndexCandidate* candidate3 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate3);
		candidate3->setColumn(&pemail_id);
		NumericScanParam numParam2(10);
		candidate3->setValue(&numParam2);

		IndexCandidate* candidate4 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate4);
		candidate4->setColumn(&pemail);
		StringScanParam strParam3(L"test2");
		candidate4->setValue(&strParam3);

		OrIndexCandidate orCandidate;
		orCandidate.add(candidate);
		orCandidate.add(candidate2);

		OrIndexCandidate orCandidate2;
		orCandidate2.add(candidate3);
		orCandidate2.add(candidate4);


		AbstractIndexCandidate* mul1 = orCandidate.multiply(&orCandidate2); __STP(mul1);
		const UnicodeString* str = mul1->toCodeString();

		UnicodeString ans(L"public.test_table.email_id = 10 AND public.test_table.id > 10 OR public.emails.email = 'test2' AND public.test_table.id > 10 OR public.test_table.email_id = 10 AND public.test_table.name = 'test' OR public.emails.email = 'test2' AND public.test_table.name = 'test'");
		CHECK(ans.equals(str));


		AbstractIndexCandidate* mul2 = mul1->copy(); __STP(mul2);
		const UnicodeString* str2 = mul2->toCodeString();
		CHECK(str2->equals(str));
	}
}

TEST(TestIndexConditionGroup, case06){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	VirtualMachine* vm = tester.getVm();

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier name(L"public", L"test_table", L"name");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"emails", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pname(&name);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);


		SelectScanPlanner* planner = new SelectScanPlanner(); __STP(planner);
		VmSelectPlannerSetter setter(vm, planner);

		pid.analyzeConditions(vm, planner);
		pname.analyzeConditions(vm, planner);
		pemail_id.analyzeConditions(vm, planner);
		pemail.analyzeConditions(vm, planner);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);
		NumericScanParam numParam(10);
		candidate->setValue(&numParam);

		IndexCandidate* candidate2 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate2);
		candidate2->setColumn(&pname);
		StringScanParam strParam2(L"test");
		candidate2->setValue(&strParam2);

		IndexCandidate* candidate3 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate3);
		candidate3->setColumn(&pemail_id);
		NumericScanParam numParam2(10);
		candidate3->setValue(&numParam2);

		IndexCandidate* candidate4 = new IndexCandidate(IndexCandidate::IndexType::EQUALS); __STP(candidate4);
		candidate4->setColumn(&pemail);
		StringScanParam strParam3(L"test2");
		candidate4->setValue(&strParam3);

		AbstractIndexCandidate* mul1 = candidate->multiply(candidate2); __STP(mul1);

		OrIndexCandidate orCandidate2;
		orCandidate2.add(candidate3);
		orCandidate2.add(candidate4);

		AbstractIndexCandidate* mul2 = mul1->multiply(&orCandidate2); __STP(mul2);
		const UnicodeString* str = mul2->toCodeString();

	//	printf(str->toCString());

		UnicodeString ans(L"public.test_table.email_id = 10 AND public.test_table.id > 10 AND public.test_table.name = 'test' OR public.emails.email = 'test2' AND public.test_table.id > 10 AND public.test_table.name = 'test'");
		CHECK(ans.equals(str));
	}
}
