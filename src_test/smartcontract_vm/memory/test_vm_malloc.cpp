
#include "test_utils/t_macros.h"

#include "vm/VirtualMachine.h"
#include "instance/instance_parts/VmMalloc.h"

using namespace alinous;

TEST_GROUP(TestVmMalloc) {
	TEST_SETUP(){}
	TEST_TEARDOWN(){}
};

struct Dummy {

};

TEST(TestVmMalloc, construct){
	VirtualMachine vm(1024);
	VmMalloc alloc(&vm);
}

TEST(TestVmMalloc, allocArray){
	VirtualMachine vm(1024);
	VmMalloc alloc(&vm);

	Dummy** ptr = (Dummy**)alloc.mallocPtrArray(4);

	alloc.releaseArray(ptr);
}
