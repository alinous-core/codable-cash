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
