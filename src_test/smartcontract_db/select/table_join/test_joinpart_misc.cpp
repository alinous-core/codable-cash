/*
 * test_joinpart_misc.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "lang_sql/sql_join_parts/TableIdentifier.h"
#include "lang_sql/sql_join_parts/TableList.h"
#include "lang_sql/sql_join_parts/SQLJoinPart.h"
#include "lang_sql/sql_join_parts/SQLJoin.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang_sql/sql_join_parts/ParenthesisJoinPart.h"

#include "engine/CdbException.h"
using namespace alinous;
//using namespace codablecash;

TEST_GROUP(TestJoinPartMiscGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestJoinPartMiscGroup, TableIdentifier01){
	TableIdentifier part;
	AnalyzedType at = part.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE)
}

TEST(TestJoinPartMiscGroup, TableList01){
	TableList part;
	AnalyzedType at = part.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE)
}

TEST(TestJoinPartMiscGroup, SQLJoinPart01){
	SQLJoinPart part;
	AnalyzedType at = part.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE)
}

TEST(TestJoinPartMiscGroup, SQLJoin01){
	SQLJoin part;
	AnalyzedType at = part.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE)
}

TEST(TestJoinPartMiscGroup, ParenthesisJoinPart01){
	ParenthesisJoinPart part;
	part.setPart(new TableIdentifier());

	AnalyzedType at = part.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE)
}

TEST(TestJoinPartMiscGroup, JoinPartException01){
	ParenthesisJoinPart part;

	CdbException* ex = nullptr;
	try{
		part.onSelectTarget(nullptr);
	}catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}


