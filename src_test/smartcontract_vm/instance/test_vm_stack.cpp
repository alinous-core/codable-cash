/*
 * test_vm_stack.cpp
 *
 *  Created on: 2020/03/09
 *      Author: iizuka
 */
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "engine/sc/SmartContract.h"
#include "base_io_stream/FileInputStream.h"

#include "base/UnicodeString.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "ext_binary/ExtPrimitiveObject.h"

#include "vm/stack/VmStack.h"

#include "engine/sc_analyze/AnalyzedType.h"
using namespace alinous;

TEST_GROUP(TestVmStackGroup) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmStackGroup, Stack){
	VirtualMachine vm(1024);

	VmStack* stack = new(&vm) VmStack(nullptr, &vm);
	CHECK(stack->getReferences() != nullptr);

	AnalyzedType at = stack->getRuntimeType();
	CHECK(at.getType() == AnalyzedType::TYPE_NONE)

	delete stack;
}

TEST(TestVmStackGroup, Stack02){
	VirtualMachine vm(1024);

	VmStack* stack = new(&vm) VmStack(nullptr, &vm);
	CHECK(stack->getReferences() != nullptr);

	stack->wrap(nullptr, &vm);
	stack->instIsNull();
	stack->getInstReferences();
	stack->instValueCompare(nullptr);
	stack->instIsPrimitive();
	stack->instToClassExtObject(nullptr, nullptr);

	stack->resetOnGc();

	delete stack;
}
