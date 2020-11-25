/*
 * test_join_conditions.cpp
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
using namespace codablecash;

TEST_GROUP(TestJoinConditionGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestJoinConditionGroup, case01){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);

		CHECK(candidate.size() == 1);
		CHECK(candidate.get(0) == &candidate);
		CHECK(candidate.getJoinType() == JoinCandidate::INNER);
		CHECK(candidate.getCandidateType() == JoinCandidate::CandidateType::EQUALS);
	}
}

TEST(TestJoinConditionGroup, case02){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"test_table", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);
		JoinCandidate candidate2(JoinCandidate::INNER, &pemail_id, &pemail);

		AbstractJoinCandidate* c3 = candidate.multiply(&candidate2); __STP(c3);

		JoinMultipleCandidate* mulCandidate = dynamic_cast<JoinMultipleCandidate*>(c3);

		CHECK(mulCandidate->size() == 2);
		CHECK(mulCandidate->get(0)->getCandidateType() == JoinCandidate::CandidateType::EQUALS);
		CHECK(mulCandidate->getJoinType() == JoinCandidate::INNER);
		CHECK(mulCandidate->getCandidateType() == JoinCandidate::CandidateType::AND);
	}
}

TEST(TestJoinConditionGroup, case03){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"test_table", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);
		JoinCandidate candidate2(JoinCandidate::INNER, &pemail_id, &pemail);

		AbstractJoinCandidate* c3 = candidate.multiply(&candidate2); __STP(c3);

		AbstractJoinCandidate* c4 = c3->copy(); __STP(c4);

		AbstractJoinCandidate* c5 = c4->multiply(c4); __STP(c5);

		JoinMultipleCandidate* mulCandidate = dynamic_cast<JoinMultipleCandidate*>(c5);
		CHECK(mulCandidate->size() == 4);
	}
}

TEST(TestJoinConditionGroup, case04){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"test_table", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);
		JoinCandidate candidate2(JoinCandidate::INNER, &pemail_id, &pemail);

		AbstractJoinCandidate* c3 = candidate.multiply(&candidate2); __STP(c3);

		AbstractJoinCandidate* c4 = c3->copy(); __STP(c4);

		JoinMultipleCandidate* mulCandidate = dynamic_cast<JoinMultipleCandidate*>(c4);

		JoinOrCandidate orCandidate(JoinCandidate::INNER);
		orCandidate.add(&candidate);
		orCandidate.add(c4);
	}
}

TEST(TestJoinConditionGroup, case05){
	TestDbSchema01 tester(this->env);
	tester.init(1024 * 10);

	{
		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		SQLColumnIdentifier email_id(L"public", L"test_table", L"email_id");
		SQLColumnIdentifier email(L"public", L"test_table", L"email");

		ColumnIdentifierScanParam pid(&id);
		ColumnIdentifierScanParam pemail_id(&email_id);
		ColumnIdentifierScanParam pemail(&email);

		JoinCandidate candidate(JoinCandidate::INNER, &pid, &pemail_id);
		JoinCandidate candidate2(JoinCandidate::INNER, &pemail_id, &pemail);

		AbstractJoinCandidate* c3 = candidate.multiply(&candidate2); __STP(c3);

		AbstractJoinCandidate* c4 = c3->copy(); __STP(c4);

		JoinMultipleCandidate* mulCandidate = dynamic_cast<JoinMultipleCandidate*>(c4);

		/**
		 * A or B
		 */
		JoinOrCandidate orCandidate(JoinCandidate::INNER);
		orCandidate.add(&candidate);
		orCandidate.add(c4);

		/**
		 * A or (B or C)
		 */
		JoinOrCandidate orCandidate2(JoinCandidate::INNER);
		orCandidate2.add(&candidate2);
		orCandidate2.add(&orCandidate);

		JoinOrCandidate* mor = dynamic_cast<JoinOrCandidate*>(orCandidate.multiply(&orCandidate2)); __STP(mor);
		CHECK(mor->size() == 6);
		CHECK(mor->get(5) != nullptr);

		JoinOrCandidate* mor2 = dynamic_cast<JoinOrCandidate*>(candidate.multiply(mor)); __STP(mor2);
		CHECK(mor2->size() == 6);

		JoinOrCandidate* mor3 = dynamic_cast<JoinOrCandidate*>(mulCandidate->multiply(mor)); __STP(mor3);
		CHECK(mor3->size() == 6);

		JoinOrCandidate* mor4 = dynamic_cast<JoinOrCandidate*>(mor3->copy()); __STP(mor4);
		CHECK(mor4->size() == 6);
	}
}
