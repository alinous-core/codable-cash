/*
 * test_select_arithmetic_contition.cpp
 *
 *  Created on: 2020/07/31
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"
#include "base_io/File.h"

#include "vm/VirtualMachine.h"
#include "vm/VmSelectPlannerSetter.h"

#include "compiler/SmartContractParser.h"

#include "alinous_lang/AlinousLang.h"

#include "sql_dml_parts/SQLWhere.h"

#include "sc_analyze/AnalyzeContext.h"

#include "scan_planner/SelectScanPlanner.h"

using namespace alinous;

TEST_GROUP(TestSelectArithmeticConditionGroup) {
	TEST_SETUP(){
	}
	TEST_TEARDOWN(){
	}
};


TEST(TestSelectArithmeticConditionGroup, add01){
	VirtualMachine* vm = new VirtualMachine(1024 * 10); __STP(vm);

	{

	}
}
