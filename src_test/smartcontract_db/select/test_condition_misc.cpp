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
