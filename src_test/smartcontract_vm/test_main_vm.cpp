/*
 * test_main_vm.cpp
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */


#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"

using namespace alinous;
using namespace codablecash;



TEST_GROUP(TestVMGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}

};

TEST(TestVMGroup, construct){
	VirtualMachine* vm = new VirtualMachine();
	delete vm;
}
