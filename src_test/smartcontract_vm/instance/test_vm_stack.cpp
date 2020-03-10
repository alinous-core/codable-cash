/*
 * test_vm_stack.cpp
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

#include "stack/VmStack.h"

using namespace alinous;

TEST_GROUP(TestVmStackGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmStackGroup, Stack){
	VirtualMachine vm(1024);

	VmStack* stack = new(&vm) VmStack(&vm);
	CHECK(stack->getReferences() != nullptr);

	delete stack;
}
