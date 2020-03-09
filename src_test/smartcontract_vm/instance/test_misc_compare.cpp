/*
 * test_misc_compare.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "instance_ref/PrimitiveReference.h"

#include "ext_binary/ExtPrimitiveObject.h"
using namespace alinous;

TEST_GROUP(TestMiscCompareGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestMiscCompareGroup, Stack){
	VirtualMachine vm(1024);

	VmStack* stack = new(vm) VmStack();
	VmStack* stack2 = new(vm) VmStack();

	int result = stack->valueCompare(stack2);
	CHECK(result == 0)

	delete stack;
	delete stack2;
}

