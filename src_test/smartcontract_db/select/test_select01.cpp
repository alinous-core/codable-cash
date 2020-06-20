/*
 * test_select01.cpp
 *
 *  Created on: 2020/06/20
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "base/StackRelease.h"

#include "../../smartcontract_vm/VmTestUtils.h"
#include "vm/VirtualMachine.h"

using namespace alinous;
//using namespace codablecash;

TEST_GROUP(TestSelect01Group) {
	TEST_SETUP(){
		env->setup();
	}
	TEST_TEARDOWN(){
		env->teardown();
	}
};

TEST(TestSelect01Group, case01){

}

