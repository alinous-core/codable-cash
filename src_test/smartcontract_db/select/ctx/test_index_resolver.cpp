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

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"


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

	{
		IndexResolver resolver(tester.getDatabase());

		SQLColumnIdentifier id(L"public", L"test_table", L"id");
		ColumnIdentifierScanParam pid(&id);

		IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE_GT); __STP(candidate);
		candidate->setColumn(&pid);

	}
}
