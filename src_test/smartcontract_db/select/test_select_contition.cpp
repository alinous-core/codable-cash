/*
 * test_select_contition.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

using namespace alinous;

TEST_GROUP(TestSelectConditionGroup) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestSelectConditionGroup, case01){

}
