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

#include "base/StackRelease.h"

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
	}
}
