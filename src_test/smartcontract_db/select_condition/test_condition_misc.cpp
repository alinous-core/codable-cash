/*
 * test_condition_misc.cpp
 *
 *  Created on: 2020/07/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "engine/CdbException.h"

#include "lang_sql/sql_expression/SQLBooleanLiteral.h"
#include "lang_sql/sql_expression/SQLEqualityExpression.h"
#include "lang_sql/sql_expression/SQLRelationalExpression.h"
#include "lang_sql/sql_expression/SQLNotExpression.h"
#include "lang_sql/sql_expression/SQLInExpression.h"
#include "lang_sql/sql_expression/SQLExpressionList.h"
#include "lang_sql/sql_expression/SQLLikeExpression.h"
#include "lang_sql/sql_expression/SQLPlaceHolder.h"
#include "lang_sql/sql_expression/SQLFunctionCall.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "instance/AbstractVmInstance.h"

#include "scan_select/scan_condition_exp/RelationalScanCondition.h"
#include "scan_select/scan_condition_exp/EqualityScanCondition.h"
#include "scan_select/scan_condition_exp/ParenthesisScanCondition.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "scan_select/scan_condition_logical/NotScanCondition.h"
#include "scan_select/scan_condition_logical/AndScanCondition.h"
#include "scan_select/scan_condition_logical/OrScanCondition.h"

#include "scan_select/scan_condition/RootScanCondition.h"

#include "scan_select/scan_condition_arithmetic/AdditiveScanCondition.h"

#include "scan_select/scan_planner/SelectScanPlanner.h"
using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestConditionMiscGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestConditionMiscGroup, sqleq01){
	SQLEqualityExpression eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, sqlRelation01){
	SQLRelationalExpression eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, sqlNot01){
	SQLNotExpression eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, sqlNot02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{
		SQLNotExpression nt;
		SQLExpressionList* list = new SQLExpressionList();

		nt.setExpression(list);

		AnalyzeContext* actx = new AnalyzeContext(); __STP(actx);
		actx->setVm(vm);

		nt.analyze(actx);

		CHECK(actx->hasError());
	}
}

TEST(TestConditionMiscGroup, sqlIn01){
	SQLInExpression eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, sqlLike01){
	SQLLikeExpression eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, bool01){
	SQLBooleanLiteral bl;
	AnalyzedType at = bl.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_BOOL);
}

TEST(TestConditionMiscGroup, bool02){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);
	{
		SQLBooleanLiteral bl;

		AbstractVmInstance* inst = bl.interpret(vm);

		delete inst;
	}
}

TEST(TestConditionMiscGroup, SQLExpressionList){
	SQLExpressionList eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE);
}

TEST(TestConditionMiscGroup, SQLPlaceHolder){
	SQLPlaceHolder eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE);
}

TEST(TestConditionMiscGroup, SQLFunctionCall){
	SQLFunctionCall eq;

	AnalyzedType at = eq.getType(nullptr);

	CHECK(at.getType() == AnalyzedType::TYPE_NONE);
}

TEST(TestConditionMiscGroup, NotScan){
	NotScanCondition notCond;

	CHECK(notCond.isContainer());
}

TEST(TestConditionMiscGroup, RootScanCondition){
	RootScanCondition cond;

	CHECK(cond.isContainer());
}

TEST(TestConditionMiscGroup, ParenthesisScanCondition){
	ParenthesisScanCondition cond;

	CHECK(cond.isContainer());
}

TEST(TestConditionMiscGroup, AndScanCondition01){
	AndScanCondition cond;
	CHECK(cond.isContainer());
}

TEST(TestConditionMiscGroup, OrScanCondition01){
	OrScanCondition cond;
	CHECK(cond.isContainer());
}

TEST(TestConditionMiscGroup, AdditiveScanCondition01){
	AdditiveScanCondition cond;
	CHECK(!cond.isContainer());
}

TEST(TestConditionMiscGroup, SelectPlanner01){
	SelectScanPlanner planner;
	RootScanCondition* cond = new RootScanCondition();

	planner.push(cond);
	AbstractScanConditionElement* cond2 = planner.top();
	CHECK(cond == cond2);
}

