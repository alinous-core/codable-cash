/*
 * test_vmemlist.cpp
 *
 *  Created on: 2019/06/06
 *      Author: iizuka
 */

#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "instance_parts/VmMalloc.h"
#include "instance_parts/VMemList.h"

#include "instance_ref/PrimitiveReference.h"

using namespace alinous;

TEST_GROUP(TestVmMemList) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

TEST(TestVmMemList, construct){
	VirtualMachine vm(1024);
	VmMalloc alloc(&vm);

	PrimitiveReference* ref = PrimitiveReference::createIntReference(&vm);
	VMemList<PrimitiveReference> list(&vm);

	delete ref;
}
