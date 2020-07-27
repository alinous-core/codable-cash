/*
 * test_condition_misc.cpp
 *
 *  Created on: 2020/07/22
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "scan_condition_exp/EqualityScanCondition.h"

#include "engine/CdbException.h"

#include "sql_expression/SQLBooleanLiteral.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "instance/AbstractVmInstance.h"

using namespace alinous;
using namespace codablecash;

TEST_GROUP(TestConditionMiscGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};

TEST(TestConditionMiscGroup, eq01){
	EqualityScanCondition eq;

	CdbException* ex = nullptr;
	try{
		eq.setLeft(nullptr);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
}

TEST(TestConditionMiscGroup, eq02){
	EqualityScanCondition eq;

	CdbException* ex = nullptr;
	try{
		eq.setRight(nullptr);
	}
	catch(CdbException* e){
		ex = e;
	}

	CHECK(ex != nullptr);
	delete ex;
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
